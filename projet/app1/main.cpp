/*
 * Fichier: main.cpp
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
#include "CapteurDistance.hpp"
#include "Rs232Robot1.hpp"

Led led(&PORTA, &DDRA, PA0, PA1);
Wheels wheels(&PORTD);
Sonorite sonorite;
CapteurDistance capteurMilieu(&DDRA, PA2, PA3);
Communication communication;
Rs232Robot1 rs232;

uint8_t nSeg = 0;
uint32_t segmentsTop[4] = {0};
uint32_t segmentsBot[4] = {0};
uint16_t posTop[4] = {0};
uint16_t posBot[4] = {0};
uint16_t lSegmentsTop[4] = {0};
uint16_t lSegmentsBot[4] = {0};
uint8_t coin1;
uint8_t coin2;

volatile uint8_t ledState = 0;

void setSegments(){
    nSeg = 3;
    lSegmentsTop[0] = 4;
    lSegmentsTop[1] = 6;
    lSegmentsTop[2] = 8;

    posTop[0] = 25;
    posTop[1] = 50;
    posTop[2] = 75;
    lSegmentsBot[0] = 4;
    lSegmentsBot[1] = 4;
    lSegmentsBot[2] = 6;
    posBot[0] = 30;
    posBot[1] = 60;
    posBot[2] = 80;
}

volatile uint8_t gBoutonPoussoir;
volatile uint8_t posRobot;

volatile bool estAllume;

void initializeR1() {
    cli();

    DDRB &= ~(1 << PB2);

    EIMSK |= (1 << INT2);
    EICRA |= (1 << ISC20) | (1 << ISC21);

    sei();
}

ISR (INT2_vect)  // pour le bouton poussoir dans mode attente
{
  _delay_ms(30);
  
  gBoutonPoussoir = 1;

  //EIFR |= (1 << INTF1); //clearing interrupt flag
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

void turnTowardsOpening(uint8_t speed) {

    uint8_t counter = 0;

    wheels.ajustementPivot(100);
    _delay_ms(100);
    bool continueTurning = true;
    while (continueTurning) {
        wheels.pivot2(speed);
        _delay_ms(20);
        if (capteurMilieu.getDistance() < 20) // quand le robot capte l'ouverture il s'arrete
            continueTurning = false;

        counter++;
    }
    wheels.stop();


    rs232.setCounter(counter);

    //cette methode nous a permis de savoir la valeur du counter:

    // initializeR1();

    // _delay_ms(100);

    // do {

    // // attendre qu'une des deux variables soit modifiée

    // // par une ou l'autre des interruptions.

    // } while ( gBoutonPoussoir == 0 );

    // cli();

    // if (gBoutonPoussoir == 1){
    // communication.transmissionUART(counter);
    // }
}

void moveToRed(uint8_t speed) {


    bool continueForward = true;

    wheels.ajustementForward(100);
    _delay_ms(100);
    while (continueForward) {


        wheels.moveForward2(speed);
        _delay_ms(20);

        if (capteurMilieu.getDistance() > 32){ // quand le robot arrive au milieu il commence a tourner
            turnTowardsOpening(40); // fait pivoter le robot jusqu'a atteinte de l'ouverture
            continueForward = false;
        }

    }
    wheels.stop();
    _delay_ms(MOVEMENT_DELAY_MS);
}

void moveBackToRed(uint8_t speed) {
    bool continueBackward = true;
    wheels.ajustementBack(100);
    _delay_ms(100);
    while (continueBackward) {

        wheels.moveBackward2(speed);
        _delay_ms(20);
  
        if (capteurMilieu.getDistance() < 44){ // quand le robot arrive au milieu il commence a tourner
            turnTowardsOpening(45); // fait pivoter le robot jusqu'a atteinte de l'ouverture
            continueBackward = false;
        }
    }
    wheels.stop();
}

// fontion qui permet au robot 1 de trouver le milieu de la boite
void trouverMilieu()
{

    uint16_t distance = capteurMilieu.getDistance();

    uint8_t speed = 50; // Vitesse de deplacement par defaut

    bool milieuTrouve = false;


    _delay_ms(5000);
    while(milieuTrouve == false)
    {
        if(distance < 44){
            rs232.setPosInitiale(1); // pour que robot 1 pointe vers centre dans schema
            moveToRed(speed); // fait avancer le robot 1 vers le point rouge
            wheels.stop();
            milieuTrouve = true;
        } else if (distance > 44){
            rs232.setPosInitiale(2); // pour que robot 1 pointe vers mur dans schema
            moveBackToRed(speed); // fait reculer le robot 1 vers le point rouge
            wheels.stop();
            milieuTrouve = true;
        }
        wheels.stop();
    }
}

// fonction pour les beeps
void playBeepSequence(int numBeeps) {
    for (uint8_t i = 0; i < numBeeps; i++) {
        sonorite.jouer(80);
        _delay_ms(BEEP_DELAY_MS);
        sonorite.arreter();
        _delay_ms(BEEP_DELAY_MS);
    }
}

// fonction pour le mode attente du robot 1
void modeR1() {

    led.turnRedOn();

    initializeR1();

    _delay_ms(100);

  do {

  // attendre qu'une des deux variables soit modifiée

  // par une ou l'autre des interruptions.

  } while ( gBoutonPoussoir == 0 );

    cli();

    if (gBoutonPoussoir == 1){
        playBeepSequence(3);
        gBoutonPoussoir = 0;
    }
}

// fonction pour recevoir les donnees par IR
void modeReception() {
    led.turnLedOff();
    _delay_ms(5000);
}

// fonction pour fair clignoter la LED en vert a 5Hz
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

// fonction pour envoi des donnes au PC du robot 1
void modeEnvoiRs232()
{

    gBoutonPoussoir = 0;
    bool donneesEnEnvoi = true;
    while(donneesEnEnvoi)
    {
        led.turnGreenOn();

        initializeR1();

        _delay_ms(100);

        do {

        // attendre qu'une des deux variables soit modifiée

        // par une ou l'autre des interruptions.

        } while ( gBoutonPoussoir == 0 );

        cli();

        if (gBoutonPoussoir == 1){
            setupTimerForBlink();
            sei();
            while (true){
                rs232.envoiDessin(posTop, lSegmentsTop, posBot, lSegmentsBot);
                break;
            }

            // Après l'envoi, vous pouvez désactiver le timer ou le laisser actif en fonction de la logique de votre programme

            donneesEnEnvoi = false;
        }

    }  
}

// fonction pour differents modes du robot 1
void modesRobot()
{
    ModeRobot mode = ModeRobot::ATTENTE;

    bool rs232Sent = false;
    bool erreurReception = false;
    while (rs232Sent == false)
    {
        switch (mode)
        {
        case ModeRobot::ATTENTE:
            modeR1();
            mode = ModeRobot::RECEPTION_IR;
            break;

        case ModeRobot::RECEPTION_IR:
            modeReception();
            if (erreurReception == true){
                sonorite.jouer(46);
                _delay_ms(1000);
                mode = ModeRobot::ATTENTE; // retour au mode attente si echec lors de reception ir
            }
            mode = ModeRobot::ENVOI_RS232;
            break;

        case ModeRobot::ENVOI_RS232:
            modeEnvoiRs232();
            mode = ModeRobot::ENVOI_RS232; // retour au mode envoi rs232
            break;
        }
    }
}

int main()
{
    DDRD = (1 << PD2) | (1 << PD3) | (1 << PD4) | (1 << PD5); // Wheels
    DDRA = ((1 << PA0) | (1 << PA1)); // Led
    DDRD |= ((1 << PD6) | (1 << PD7)); // Sonorite

    trouverMilieu();

    setSegments();

    modesRobot();

    return 0;
}
