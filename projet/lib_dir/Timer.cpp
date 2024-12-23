
/*
 * Fichier: Timer.cpp
 *
 * Description:
 * Ce fichier implemente les methodes de la classe Timer. Ces methodes permettent de demarrer un
 * timer en mode CTC ou en mode PWM ainsi que d'arreter ces timers.
 * 
 * Identifications matérielles :
 * - Microcontrôleur : ATmega324PA
 * - Minuterie interne
 */

#ifndef TIMER_H
#define TIMER_H
#define F_CPU 8000000UL

#include "Timer.hpp"

Timer::Timer(uint8_t numeroTimer)
{
    numeroTimer_ = numeroTimer;
}
void Timer::startTimerCtc(uint8_t time)
{
    cli();
    if (numeroTimer_ == 0)
    {
        TCNT0 = 0;
        OCR0A = time;
        TCCR0A = (1 << WGM01); //(1<<COM0A0) | (1<<COM0A1)
        TCCR0B = (1 << CS02) | (1 << CS00); // (1 << WGM02) | 
        TIMSK0 = (1 << OCIE0A);
    }
    else if (numeroTimer_ == 1)
    {
        TCNT1 = 0;
        OCR1A = time;
        TCCR1A = (1<<COM1A0) | (1<<COM1B0) | (1<<COM1A1) | (1<<COM1B1);
        TCCR1C = 0;
        TIMSK1 = (1 << OCIE1A);
    }
    else if (numeroTimer_ == 2)
    {
        TCNT2 = 0;
        OCR2A = time;
        TCCR2A = (1<<COM2A0) | (1<<COM2B0) | (1<<COM2A1) | (1<<COM2B1);
        TIMSK2 = (1 << OCIE2A);
    }
    sei();
}

void Timer::startTimerPwm(uint8_t pwm)
{
    if (numeroTimer_ == 0)
    {
        OCR0A = (255 * pwm)/100;
        OCR0B = (255 * pwm)/100;
        TCCR0B = (1 << CS02) | (1 << CS00);
        TCCR0A = (1<<WGM00) | (1<<COM0A1) | (1<<COM0B1) ;
    }
    else if (numeroTimer_ == 1)
    {
        OCR1A = (255 * pwm)/100;
        OCR1B = (255 * pwm)/100;

        TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
        TCCR1C = 0;
    }
    else if (numeroTimer_ == 2)
    {
        //OCR2A = (255 * pwm)/100;
        //OCR2B = (255 * pwm)/100;

        TCCR2A = (1<<WGM21) | (1<<COM2A0) ;
    }//| (1<<COM2B1) 
}

void Timer::stopTimerCtc()
{
    cli();
    if (numeroTimer_ == 0)
    {
        TCCR0A = 0; 
        TCCR0B = 0;
        TIMSK0 = 0;
    }
    else if (numeroTimer_ == 1)
    {
        TCCR1A = 0; 
        TCCR1B = 0;
        TCCR1C = 0;
        TIMSK1 = 0;
    }    
    else if (numeroTimer_ == 2)
    {
        TCCR2A = 0; 
        TCCR2B = 0;
        TIMSK2 = 0;
    }
    sei();
}

void Timer::stopTimerPwm()
{
    if (numeroTimer_ == 0)
    {
        TCCR0A = 0; 
        TCCR0B = 0;
        TIMSK0 = 0;
        OCR0A = 0;
        OCR0B = 0;
    }
    else if (numeroTimer_ == 1)
    {
        TCCR1A = 0; 
        TCCR1B = 0;
        TCCR1C = 0;
        TIMSK1 = 0;
    }    
    else if (numeroTimer_ == 2)
    {
        TCCR2A = 0; 
        TCCR2B = 0;
        TIMSK2 = 0;
    }
}
#endif