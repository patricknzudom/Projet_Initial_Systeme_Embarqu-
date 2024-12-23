/*
 * Fichier: Led.h
 * 
 * Description:
 * La classe Led permet de controller la led du robot. Elle permet de l'allumer rouge, vert et de l'eteindre.
 * Une alternation rapide entre rouge et vert permet d'obtenir une couleur ambre.
 *
 * Identifications matérielles :
 * - Microcontrôleur : ATmega324PA
 * - Led bicolore
 */
#ifndef LED_H
#define LED_H
#include "interfaces/utils.hpp"
#include "util/delay.h"
#include "Timer.hpp"
//#include "interfaces/consts_lib.hpp"

class Led 
{
public:
    Led() = default;

    Led(Register port, Register mode, uint8_t pinGreen, uint8_t pinRed); // Constructeur Led

    ~Led()= default;// Destructeur Led

    void turnLedOff(); // Eteindre led

    void turnGreenOn(); // Allumer led vert

    void turnRedOn(); // Allumer led rouge

private:
    Register port_;    // Le registre du port de la LED.
    Register mode_;    // Le registre de mode du port de la LED.
    uint8_t pinGreen_; // Numero de broche de la LED verte.
    uint8_t pinRed_;   // Numero de broche de la LED rouge.
};

#endif // LED_H
