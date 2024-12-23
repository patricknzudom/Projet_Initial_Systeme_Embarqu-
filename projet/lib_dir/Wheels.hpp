/**
 * Fichier: Wheel.hpp
 * 
 * Description:
 * La classe Wheel permet de démarrer, arrêter, et changer la direction de la roue
 * motorisée. Elle utilise un Timer pour la modulation de largeur d'impulsion (PWM)
 * afin de contrôler la vitesse de la roue.
 * 
 * Identification matérielle :
 * - Microcontrôleur : ATmega324PA
 * 
 */
#ifndef WHEELS_H
#define WHEELS_H
#include "Timer.hpp"
#include "interfaces/utils.hpp"
#include "util/delay.h"

class Wheels
{
public:
    Wheels() = default;

    Wheels(volatile uint8_t* directionPort);

    ~Wheels() = default; // Destructeur Wheel

    void moveForward(uint8_t speed); // Fait tourner la roue vers l'avant à la vitesse souhaitée.

    void moveForward2(uint8_t speed);

    void ajustementForward(uint8_t speed);

    void moveBackward(uint8_t speed); // Fait tourner la roue vers l'arrière à la vitesse souhaitée.

    void moveBackward2(uint8_t speed);

    void ajustementBack(uint8_t speed);

    void turnRight(uint8_t speed); 

    void turnLeft(uint8_t speed); 

    void ajusterRight(uint8_t speed);

    void ajusterLeft(uint8_t speed);

    void backRight(uint8_t speed);

    void backLeft(uint8_t speed);

    void pivot(uint8_t speed);

    void pivot2(uint8_t speed);

    void ajustementPivot(uint8_t speed);

    void unblock();

    void unblockP();

    void unblockB();

    void unblockR();

    void unblockL();

    void stop(); //Stop la roue.

private:
    //Timer timer_;               // Pointeur vers le Timer 0 utilisé pour le PWM.
    volatile uint8_t* wheelDirectionPort_;    // Port qui permet de contrôler la direction de la roue.
};

#endif
