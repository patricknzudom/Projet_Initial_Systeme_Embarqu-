/*
 * Fichier: Button.hpp
 *
 * Description:
 * La classe Button permet de configurer le bouton-poussoir du robot
 * pour lui permettre d'etre utiliser pour generer des interruptions 
 * ou pour l'utiliser en scrutation.
 * 
 * Identifications matérielles :
 * - Microcontrôleur : ATmega324PA
 */
 
 #pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include <util/delay.h>
#include "interfaces/utils.hpp"
#include "interfaces/emun/ButtonMode.hpp"

class Button {
public:
    Button(Register mode, Register pin, uint8_t pinNumber, const ButtonMode &buttonMode); // Constructeur Button

    ~Button(); // Destructeur Button

    bool pressed(); // Verification de si le bouton est appuye

    bool highSignal(uint8_t press);

    bool stableSignal(uint8_t press, uint8_t check);

private:
    Register pin_;
    ButtonMode buttonMode_;
    uint8_t pinNumber_;
    static const uint8_t DEBOUNCE_DELAY_MS = 30;
};
#endif