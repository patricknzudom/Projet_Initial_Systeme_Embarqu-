/*
 * Fichier: Sonorite.hpp
 *
 * Description:
 * 
 * Identifications matérielles :
 * - Microcontrôleur : ATmega324PA
 */
 
 #pragma once

#ifndef SONORITE_H
#define SONORITE_H

#include <avr/io.h>
#include "Timer.hpp"
#include "interfaces/utils.hpp"
#include "util/delay.h"

class Sonorite {
public: 
    Sonorite();

    void jouer(uint8_t note);

    void arreter();

    double noteToFrequence(uint8_t note);

    void jouerTest();

private:
    Timer timer_;

};

#endif