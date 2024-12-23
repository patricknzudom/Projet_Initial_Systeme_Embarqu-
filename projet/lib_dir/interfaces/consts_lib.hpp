#ifndef CONSTS_LIB_H
#define CONSTS_LIB_H

#include <stdint.h>
#include <avr/io.h>

//=========================================================== Led
static const uint8_t DELAY_GREEN_MS = 15;       // Durée d'allumage de la LED verte en millisecondes.
static const uint8_t DELAY_RED_MS = 10;         // Durée d'allumage de la LED rouge en millisecondes.

//=========================================================== Instructions
static const uint8_t DELAY_ATT_MS = 25;          // Durée intruction ATT 25 en millisecondes.
static const uint16_t DELAY_90_MS = 1700;          // Durée intruction ATT 25 en millisecondes.

//========================================================== CapteurDistance
const uint8_t PRECISION_BIT_SHIFT = 2;
const uint8_t A2_POSITION = 2;
static const uint8_t NOMBRE_LECTURE = 10;

const uint8_t DELAY_BETWEEN_READ = 5;
const uint8_t MIN_DISTANCE_TO_DETECT = 38;
const uint8_t MAX_DISTANCE_TO_DETECT = 43;
const uint8_t DISTANCE_TO_OPENING = 100;

const uint16_t MOVEMENT_DELAY_MS = 2000;
const uint8_t MAX_ATTEMPTS = 10;

const uint8_t BEEP_DELAY_MS = 50;

#endif