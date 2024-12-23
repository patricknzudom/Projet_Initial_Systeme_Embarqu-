/*
 * Fichier: Timer.h
 * 
 * Description:
 * La classe Timer permet de rapidement partir une minuterie (0, 1 ou 2) en mode PWM ou CTC.
 * Elle permet aussi d'arreter ces timers facilement.
 * Identifications matérielles :
 * - Microcontrôleur : ATmega324PA
 * - Minuterie interne
 */

#pragma once
#include <avr/interrupt.h>
#include <avr/io.h>
#define TIMER_H
#define F_CPU 8000000UL

class Timer 
{
public:
    Timer() = default;
    Timer(uint8_t numeroTimer); // Cosntructeur Timer

    ~Timer() = default;

    void startTimerCtc(uint8_t time);

    void stopTimerCtc();

    void startTimerPwm(uint8_t pwm);

    void stopTimerPwm();

private:

    uint8_t numeroTimer_ = 0;
};
