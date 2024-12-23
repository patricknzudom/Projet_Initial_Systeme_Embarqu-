/*
 * Fichier: Sonorite.cpp
 *
 * Description:
 * 
 * Identifications matérielles :
 * - Microcontrôleur : ATmega324PA
 * - Led bicolore
 */
#include "Sonorite.hpp"

Sonorite::Sonorite(): timer_(2) {
    setRegisterBits(&DDRD, PD6);
    clearRegisterBits(&PORTD, PD6);
    setRegisterBits(&DDRD, PD7);
}

double Sonorite::noteToFrequence(uint8_t note) {
    const double frequences[] = {
        110.00,
        116.54,
        123.47,
        130.81,
        138.59,
        146.83,
        155.56,
        164.81,
        174.61,
        185.00,
        196.00,
        207.65,
        220.00,
        233.08,
        246.94,
        261.63,
        277.18,
        293.66,
        311.13,
        329.63,
        349.23,
        369.99,
        392.00,
        415.30,
        440.00,
        466.16,
        493.88,
        523.25,
        554.37,
        587.33,
        622.25,
        659.26,
        698.46,
        739.99,
        783.99,
        830.61,
        880.00,
    };

    if (note < 45 || note > 81) {
        return 0.0;
    }
    return frequences[note - 45];
}

void Sonorite::jouer(uint8_t note) {
    double frequence = noteToFrequence(note);
    if (frequence > 0.0) {
        uint16_t ocr2a = (F_CPU / (2 * 256 * frequence) - 1);
        TCCR2A = (1 << WGM21);
        TCCR2B = (1 << CS22);
        OCR2A = ocr2a;
        TCCR2A |= (1 << COM2A0);
    }
}       

void Sonorite::arreter() {
    clearRegisterBits(&TCCR2A, COM2A0);
    clearRegisterBits(&PORTD, PD7);
}

void Sonorite::jouerTest() { // Nice
    jouer((50));
    _delay_ms(125); 
    _delay_ms(10);
    jouer((52));
    _delay_ms(125);
    _delay_ms(10);
    jouer((55));
    _delay_ms(125);
    _delay_ms(10);
    jouer((52));
    _delay_ms(125);
    _delay_ms(10);
    jouer((59));
    _delay_ms(375);
    _delay_ms(20);
    jouer((59));
    _delay_ms(375);
    _delay_ms(10);
    jouer((57));
    _delay_ms(500);
    _delay_ms(30);
    jouer((50));
    _delay_ms(125); 
    _delay_ms(15);
    jouer((52));
    _delay_ms(125);
    _delay_ms(15);
    jouer((55));
    _delay_ms(125);
    _delay_ms(10);
    jouer((52));
    _delay_ms(125);
    _delay_ms(10);
    jouer((57));
    _delay_ms(375);
    _delay_ms(20);
    jouer((57));
    _delay_ms(375);
    _delay_ms(10);
    jouer((55));
    _delay_ms(375);
    _delay_ms(5);
    jouer((54));
    _delay_ms(125);
    _delay_ms(5);
    jouer((52));
    _delay_ms(250);
    _delay_ms(20);
    jouer((50));
    _delay_ms(125); 
    _delay_ms(10);
    jouer((52));
    _delay_ms(125);
    _delay_ms(10);
    jouer((55));
    _delay_ms(125);
    _delay_ms(10);
    jouer((52));
    _delay_ms(125);
    _delay_ms(10);
    jouer((55));
    _delay_ms(375);
    _delay_ms(10);
    jouer((57));
    _delay_ms(250);
    _delay_ms(10);
    jouer((54));
    _delay_ms(375);
    _delay_ms(10);
    jouer((52));
    _delay_ms(125);
    _delay_ms(15);
    jouer((50));
    _delay_ms(250);
    _delay_ms(30);
    jouer((50));
    _delay_ms(500);
    jouer((50));
    _delay_ms(500);
    _delay_ms(20);
    jouer((57));
    _delay_ms(750);
    _delay_ms(10);
    jouer((55));
    _delay_ms(1250);
    arreter();
}
