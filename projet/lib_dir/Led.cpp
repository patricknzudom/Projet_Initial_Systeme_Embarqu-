/*
 * Fichier: Led.cpp
 *
 * Description:
 * Ce fichier implemente les methodes de la classe Led. Ces methodes permettent d'allumer la led
 * de couleur verte, rouge et de l'eteindre.
 * 
 * Identifications matérielles :
 * - Microcontrôleur : ATmega324PA
 * - Led bicolore
 */
#include "Led.hpp"

Led::Led(Register port, Register mode, uint8_t pinGreen, uint8_t pinRed) : port_(port), mode_(mode), pinGreen_(pinGreen), pinRed_(pinRed)
{
    setRegisterBits(mode_, pinGreen_);
    setRegisterBits(mode_, pinRed_);
}

void Led::turnLedOff()
{
    clearRegisterBits(port_, pinGreen_);
    clearRegisterBits(port_, pinRed_);
}

void Led::turnGreenOn()
{
    turnLedOff();
    setRegisterBits(port_, pinGreen_);
}

void Led::turnRedOn()
{
    turnLedOff();
    setRegisterBits(port_, pinRed_);
}
