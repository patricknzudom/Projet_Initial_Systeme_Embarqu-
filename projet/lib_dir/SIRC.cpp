#define F_CPU 8000000UL
#include <avr/io.h>
#include "interfaces/utils.hpp"
#include <util/delay.h>
#include "SIRC.hpp"

const int DELAY_HIGH = 8.5; //Duree de l etat haut
const int DELAY_LOW = 17.5; //Duree de l etat bas
const int DELAY_1CYCLE = 26; // Durée dun cycle

SIRC::SIRC() {
    DDRA |= (1 << PA4);
}

void SIRC::burst38kHz(int duration_us) {
    int cycles = (duration_us / DELAY_1CYCLE);
    for (int i = 0; i < cycles; ++i) {
        PORTA |= (1 << PA4); // Signal haut
        _delay_us(DELAY_HIGH);
        PORTA &= ~(1 << PA4); // Signal bas
        _delay_us(DELAY_LOW);
    }
}

void SIRC::sendBit(int bit) {
    if (bit) {
        burst38kHz(BIT_1_DURATION);
    } else {
        burst38kHz(BIT_0_DURATION);
    }
    _delay_us(STANDARD_SPACE);
}

void SIRC::send(int command, int address) {
    burst38kHz(START_BURST_DURATION); // Burst de départ
    _delay_us(STANDARD_SPACE); // Espace standard après le burst de départ
    // Envoyer la commande (7 bits)
    for (int i = 0; i < 7; ++i) {
        sendBit(command & (1 << i));
    }
    // Envoyer l'adresse (8 bits pour la version 15 bits du protocole)
    for (int i = 0; i < 8; ++i) {
        sendBit(address & (1 << i));
    }
    _delay_us(STANDARD_SPACE);
}
