/*
 * Fichier: jeanmichel.cpp
 *
 * Description:
 * Point d'entrée du programme. Initialise le système et démarre les routines principales.
 * 
 * Identifications matérielles :
 * - Microcontrôleur : ATmega324PA
 */

#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "Led.hpp"
#include "Wheels.hpp"
#include "Communication.hpp"
#include "Memoire_24.h"
#include "Sonorite.hpp"
#include "SIRC.hpp"
#include "Rs232.hpp"

volatile uint8_t ledState = 0;

const uint8_t SENSOR1 = (1 << PC0);
const uint8_t SENSOR2 = (1 << PC1);
const uint8_t SENSOR3 = (1 << PC2);
const uint8_t SENSOR4 = (1 << PC3);
const uint8_t SENSOR5 = (1 << PC4);
const uint8_t BOUTON =  (1 << PA2);

const uint16_t BASE_TIME = 150;

volatile uint32_t counter = 0;
volatile uint32_t temp = 0;
uint8_t press = 0;

uint16_t smallSegTime = 52;
uint16_t medSegTime = 90;

double vMult = 1;
double vitesse = 60;

uint8_t nSeg = 0;
uint16_t nSegBot = 0;
uint16_t nSegTop = 0;
uint32_t segmentsTop[4] = {0};
uint32_t segmentsBot[4] = {0};
uint16_t posTop[4] = {0};
uint16_t posBot[4] = {0};
uint16_t lSegmentsTop[4] = {0};
uint16_t lSegmentsBot[4] = {0};
uint8_t coin1;
uint8_t coin2;

Led led(&PORTA, &DDRA, PA0, PA1);
Memoire24CXXX memory;
Wheels wheels(&PORTD);
Sonorite sonorite;
Timer timer(0);
SIRC sirc;
Rs232 RS232;

void ajustementAvancer() 
{
    PORTD &= ~((1 << PD2) | (1 << PD3));

    if ((PINC & SENSOR3) && !(PINC & (SENSOR1 | SENSOR2 | SENSOR4 | SENSOR5))){
        wheels.moveForward(vitesse);
    }
    else if ((PINC & SENSOR2 & SENSOR1) || (PINC & SENSOR2 & SENSOR3) || ((PINC & SENSOR2) && !(PINC & (SENSOR4 | SENSOR5))) || ((PINC & SENSOR1) && !(PINC & (SENSOR4 |
    SENSOR5)))) {
        wheels.ajusterRight(vitesse);
    }
    else if ((PINC & SENSOR4 & SENSOR5) || (PINC & SENSOR4 & SENSOR3) || ((PINC & SENSOR4) && !(PINC & (SENSOR1 | SENSOR2))) || ((PINC & SENSOR5) && !(PINC & (SENSOR1 |
    SENSOR2)))){
        wheels.ajusterLeft(vitesse);
    }
    else {
        wheels.moveForward(vitesse);
    }
}

void myDelay(double temps) {
    for (uint8_t i = 0; i < temps; i++){
        _delay_ms(10);
    }
}

void centrer(uint8_t temps)
{
    wheels.stop();
    _delay_ms(1000);
    wheels.moveForward(70 * vMult);
    myDelay(temps * vMult * 1.5); // temps pour avancer le robot
    wheels.stop();
    _delay_ms(1000);
}

void checkSeg() {
    centrer(100);
    wheels.unblockB();
    wheels.backRight(43 * vMult);
    _delay_ms(500);
    while (true){
        if(PINC & SENSOR4){
            wheels.stop();
            _delay_ms(1000);
            break;
        }
    }
}

void finalSeg() {
    centrer(110);
    wheels.unblockB();
    wheels.backLeft(43 * vMult);
    _delay_ms(500);
    while (true){
        if(PINC & SENSOR2){
            wheels.stop();
            _delay_ms(1000);
            break;
        }
    }
}

void turnRight90(uint8_t temps) {
    centrer(temps);
    wheels.unblockR();
    wheels.turnRight(47 * vMult);
    _delay_ms(800); // TODO : voir si c assez de temps pour faire tourner 90 degree ou ajustement wheels.turnRight()
    while(true) {
        if (PINC & SENSOR4) {
        wheels.stop();
        _delay_ms(1000);
        break;
        }
    }
}

void turnLeft90(uint8_t temps) {
    centrer(temps);
    wheels.unblockL();
    wheels.turnLeft(47 * vMult);
    _delay_ms(800);
    while(true) {
        if (PINC & SENSOR2) {
        wheels.stop();
        _delay_ms(1000);
        break;
        }
    }
}

void uTurn() {
    centrer(100);
    wheels.unblockP();
    wheels.pivot(40 * vMult);
    _delay_ms(500); // TODO : voir si c assez de temps pour faire tourner 90 degree ou ajustement wheels.turnRight()
    while(true) {
        if (PINC & SENSOR4) {
        wheels.stop();
        _delay_ms(1000);
        break;
        }
    }
}

ISR (TIMER0_COMPA_vect) {
    counter++;
}

ISR (INT2_vect) {
    press = 1;
    // anti-rebond
    //_delay_ms(10);
}

void setSpeed() {
    vMult = counter / BASE_TIME;
    if (vMult > 1.40){ // Pour pas depasser un pwm de 100
        vMult = 1.40;
    }
    if (vMult < 1){
        vMult = 1;
    }
    vitesse = vMult * vitesse;
    smallSegTime = smallSegTime * vMult;
    medSegTime = medSegTime * vMult;

    counter = 0;
}

void calculerTop(){
    uint32_t total = coin1;
    for (uint8_t i = 0; segmentsTop[i] != 0; i++){ //calcul distance total 
        total += segmentsTop[i];
        if (i == 0){
            posTop[i] = segmentsTop[i];
        }
        else{
            posTop[i] = segmentsTop[i] + posTop[i - 1];
        }
    }
    for (uint8_t i = 0; posTop[i] != 0; i++){ // conversion pourcentage
        posTop[i] = posTop[i] * 100 / total;
    }
    if (posTop[0] != 0){
        posTop[0] -= 5;
    }
    if (posTop[0] < 20){
        posTop[0] = 20;
    }
}

void calculerBot(){
    uint32_t total = coin2;
    for (uint8_t i = 0; segmentsBot[i] != 0; i++){
        total += segmentsBot[i];
        if (i == 0){
            posBot[i] = segmentsBot[i];
        }
        else{
            posBot[i] = segmentsBot[i] + posBot[i - 1];
        }
    }
    for (uint8_t i = 0; posBot[i] != 0; i++){ //conversion pourcentage
        posBot[i] = posBot[i] * 100 / total;
    }
    if (posBot[0] != 0){
        posBot[0] -= 5;
    }
    if (posBot[0] < 20){
        posBot[0] = 20;
    }
}

enum Parcours { // garder fonction dans ce fichier mais mettre le switch case dans un autre fichier
    TEST,
    INIT,
    TOP,
    SEGTOP,
    CALCUL,
    BOTTOM,
    SEGBOT,
    FINAL,
    ATT,
    SEND,
    UPLOAD,
    END
};

void sortTop() {
    timer.stopTimerCtc();
    wheels.stop();
    led.turnLedOff();
    _delay_ms(1000);

    if (counter <= smallSegTime){
        led.turnGreenOn();
        lSegmentsTop[nSeg - 1] = 4;
    }
    else if (counter <= medSegTime){
        led.turnLedOff();
        lSegmentsTop[nSeg - 1] = 6;
    }
    else {
        led.turnRedOn();
        lSegmentsTop[nSeg - 1] = 8;
    }
    _delay_ms(1000);
    led.turnLedOff();
}

void sortBot() {
    timer.stopTimerCtc();
    wheels.stop();
    led.turnLedOff();
    _delay_ms(1000);

    if (counter <= smallSegTime){
        led.turnGreenOn();
        lSegmentsBot[nSeg - 1] = 4;
    }
    else if (counter <= medSegTime){
        led.turnLedOff();
        lSegmentsBot[nSeg - 1] = 6;
    }
    else {
        led.turnRedOn();
        lSegmentsBot[nSeg - 1] = 8;
    }
    _delay_ms(1000);
    led.turnLedOff();
}


void clignoter5Hz()
{
    for (int i = 0; i<5; i++)
    {
        led.turnGreenOn();
        _delay_ms(100);
        led.turnLedOff();
        _delay_ms(100);
    }
}


ISR(TIMER1_COMPA_vect) {
    // Basculez l'état de la LED
    if (ledState) {
        led.turnLedOff();
        ledState = 0;
    } else {
        led.turnGreenOn();
        ledState = 1;
    }
}

void setupTimerForBlink() {
    TCCR1B |= (1 << WGM12); // Mode CTC
    OCR1A = 779; // Valeur pour 100 ms à 8 MHz et prescaler de 1024
    TIMSK1 |= (1 << OCIE1A); // Active l'interruption pour OCR1A
    TCCR1B |= (1 << CS12) | (1 << CS10); // Prescaler de 1024
}

int main()
{
    cli();
    DDRC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2) | (1 << PC3) | (1 << PC4)); //PC0 a PC4 = Sensor1 a Sensor5
    DDRD = (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5); // Wheels
    DDRA = ((1 << PA0) | (1 << PA1)); // Led
    DDRA &= ~((1 << PA2) | (1 << PA3)); // Boutton poussoir
    DDRB &= ~(1 << PB2); // Boutton Interrupt
    DDRD |= ((1 << PD6) | (1 << PD7)); // Sonorite
    DDRA |= (1 << PA4);;// Led IR

    EICRA |= (1 << ISC20);
    EICRA &= ~(1 << ISC21);
    EIMSK |= (1 << INT2) ;    
    sei ();

    Communication::initializeUART();

    Parcours parcoursCourant = INIT; 
    while(true) {
        switch(parcoursCourant) {
            case TEST:
                while (true) {
                    Communication::transmissionUART(lSegmentsTop[0]);
                    Communication::transmissionUART(lSegmentsTop[1]);
                    Communication::transmissionUART(lSegmentsTop[2]);
                    Communication::transmissionUART(posTop[0]);
                    Communication::transmissionUART(posTop[1]);
                    Communication::transmissionUART(posTop[2]);
                    Communication::transmissionUART(lSegmentsBot[0]);
                    Communication::transmissionUART(lSegmentsBot[1]);
                    Communication::transmissionUART(lSegmentsBot[2]);
                    Communication::transmissionUART(posBot[0]);
                    Communication::transmissionUART(posBot[1]);
                    Communication::transmissionUART(posBot[2]);
                    led.turnGreenOn();
                    _delay_ms(500);
                    led.turnRedOn();
                    _delay_ms(500);
                }
                break;

            case INIT :
                counter = 0;
                timer.startTimerCtc(100); 
                wheels.unblock();
                while(true) {
                    ajustementAvancer();
                    if ((PINC & SENSOR3) && (PINC & SENSOR5)) { // mettre la condition en constante pour facilite lecture?
                        timer.stopTimerCtc();
                        setSpeed();
                        turnRight90(50);
                        parcoursCourant = TOP;
                        break; // Sort de la boucle while
                    }
                }
                break; // Sort du cas de letat
            
            case TOP :
                counter = 0;
                timer.startTimerCtc(100);
                wheels.unblock();
                while(true) {
                    ajustementAvancer();
                    if ((PINC & SENSOR3) && (PINC & SENSOR5)) {
                        timer.stopTimerCtc();
                        temp = counter;
                        parcoursCourant = SEGTOP;//**
                        break;
                    }
                }
                break;
            
            case SEGTOP :
                checkSeg();
                counter = 0;
                timer.startTimerCtc(100);
                wheels.unblock();
                while (true) {
                    ajustementAvancer(); // Parcours le segment
                    if (!(PINC)) {
                        nSeg++;
                        nSegTop++;
                        segmentsTop[nSeg - 1] = temp;
                        sortTop();
                        uTurn();
                        while (true){
                            ajustementAvancer();
                            if((PINC & SENSOR3) && (PINC & SENSOR5)) {
                                turnRight90(50);
                                parcoursCourant = TOP;
                                break;
                            }
                        }
                        break;
                    }
                    else if ((PINC & SENSOR3) && (PINC & SENSOR5)) { // Rendu dans le coin (point F) **changer pour s5 uniquement
                        coin1 = temp;
                        turnRight90(50);
                        parcoursCourant = CALCUL;
                        break;
                    }
                }
                break;

            case CALCUL:
                wheels.stop();
                calculerTop();
                nSeg = 0;
                //parcoursCourant = TEST;
                parcoursCourant = BOTTOM;
                break;

            case BOTTOM :
                counter = 0;
                timer.startTimerCtc(100);
                wheels.unblock();
                while(true) {
                    ajustementAvancer();
                    if ((PINC & SENSOR3) && (PINC & SENSOR5)) {
                        timer.stopTimerCtc();
                        temp = counter;
                        parcoursCourant = SEGBOT;
                        break;
                    }
                }
                break;
            
            case SEGBOT :
                checkSeg();
                counter = 0;
                timer.startTimerCtc(100);
                wheels.unblock();
                while (true) {
                    ajustementAvancer(); // Parcours le segment
                    if (!(PINC)) {
                        nSeg++;
                        nSegBot++;
                        segmentsBot[nSeg - 1] = temp;
                        sortBot();
                        uTurn();
                        while (true){
                            ajustementAvancer();
                            if((PINC & SENSOR3) && (PINC & SENSOR5)) {
                                turnRight90(50);
                                parcoursCourant = BOTTOM;
                                break;
                            }
                        }
                        break;
                    }
                
                    else if ((PINC & SENSOR3) && (PINC & SENSOR1)) { // Rendu dans le coin (point F) **changer pour s5 uniquement
                        coin2 = temp;
                        finalSeg();
                        parcoursCourant = FINAL;
                        break;
                    }
                }
                break;
            
            case FINAL :
                wheels.stop();
                calculerBot();
                _delay_ms(1000);
                while(true) {
                    ajustementAvancer();
                    if (!(PINC)) {
                        wheels.stop();
                        parcoursCourant = ATT;
                        break;
                    }
                }
                break;
            
            case ATT :     
                led.turnRedOn();
                    if (~(PINA) & BOUTON) {
                        parcoursCourant = UPLOAD;
                        break;
                    }
                    else if (press == 1) {
                        parcoursCourant = SEND;
                        break;
                    }
                parcoursCourant = ATT;
                break;

            case SEND : // Envoie IR
                for (uint8_t i = 0; i < 3; i++) {
                    sonorite.jouer(80);
                    _delay_ms(50);
                    sonorite.arreter();
                    _delay_ms(50);
                }
                led.turnLedOff();
                _delay_ms(2000);

                
                for (uint8_t i = 0; i < 3; i++) {
                    if (segmentsTop[i] != 0) { // Verifier si le segment existe
                        sirc.send(posTop[i], lSegmentsTop[i]);
                        _delay_ms(50); // delai entre les envois
                    }
                }
                

                //envoyer signal qu on est rendu en bottom

                for (uint8_t i = 0; i < 3; i++) {
                    if (segmentsBot[i] != 0) { 
                        sirc.send(posBot[i], lSegmentsBot[i]);
                        _delay_ms(50);
                    }
                }
                press = 0;
                parcoursCourant = ATT;      
                break;

            case UPLOAD : // Envoie RS232
                setupTimerForBlink();
                sei(); 
                while(true)
                {
                    if (parcoursCourant == UPLOAD) {
                        RS232.envoiDessin(posTop, lSegmentsTop, posBot, lSegmentsBot, nSegTop, nSegBot);
                        
                        parcoursCourant = ATT; // Passe à l'état suivant
                    }
                    break;
                }
                break;

            case END : 
                while(true) {
                    sonorite.jouerTest();
                }
        }
    }
}
