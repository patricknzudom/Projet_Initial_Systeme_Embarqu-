 /*
  * Fichier: Wheel.cpp
  *
  * Description:
  * Ce fichier implemente les methodes de la classe Wheel pour gérer les mouvements d'une Wheel
  * Ces méthodes permettent de démarrer, stopper et changer la direction d'une Wheel avec un Timer
  * pour le PWM.
  * interruptions ou avec scrutations.
  *
  * Identifications matérielles :
  * - Microcontrôleur : ATmega324PA
  */
#include "Wheels.hpp"
#include <avr/io.h>

Wheels::Wheels(volatile uint8_t* directionPort)
{
    wheelDirectionPort_ = directionPort;
    *wheelDirectionPort_ |= (1 << PD2) | (1 << PD3);
};

void Wheels::moveForward(uint8_t speed) // fonction pour robot 2
{
    *wheelDirectionPort_ &= ~((1 << PD2) | (1 << PD3));
    OCR1A = (255 * speed)/100;
    OCR1B = (255 * speed)/100;
    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
    TCCR1B = (1<<CS11) ;
    TCCR1C = 0;
}

void Wheels::moveForward2(uint8_t speed) // fonction pour robot 1
{
    *wheelDirectionPort_ &= ~((1 << PD2) | (1 << PD3));
    OCR1A = (255 * speed)/100;
    OCR1B = (255 * speed * 1.2)/100;
    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
    TCCR1B = (1<<CS11) ;
    TCCR1C = 0;
}

void Wheels::ajustementForward(uint8_t speed) // fonction pour robot 1
{
    *wheelDirectionPort_ &= ~((1 << PD2) | (1 << PD3));
    OCR1A = (255 * speed)/100;
    OCR1B = (255 * speed)/100;
    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
    TCCR1B = (1<<CS11) ;
    TCCR1C = 0;
}

void Wheels::moveBackward(uint8_t speed) // fonction pour robot 2
{
    *wheelDirectionPort_ |= ((1 << PD3) | (1 << PD2));
    OCR1A = ((255 * speed))/100;
    OCR1B = ((255 * speed)/100);
    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
    TCCR1B = (1<<CS11) ;
    TCCR1C = 0; 
}

void Wheels::moveBackward2(uint8_t speed) // fonction pour robot 1
{
    *wheelDirectionPort_ |= ((1 << PD3) | (1 << PD2));
    OCR1A = ((255 * speed))/100;
    OCR1B = ((255 * speed * 1.2)/100);
    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
    TCCR1B = (1<<CS11) ;
    TCCR1C = 0; 
}

void Wheels::ajustementBack(uint8_t speed) // fonction pour robot 1
{
    *wheelDirectionPort_ |= ((1 << PD3) | (1 << PD2));
    OCR1A = ((255 * speed))/100;
    OCR1B = ((255 * speed)/100);
    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
    TCCR1B = (1<<CS11) ;
    TCCR1C = 0; 
}

void Wheels::turnRight(uint8_t speed)
{
    *wheelDirectionPort_ &= ~((1 << PD3) | (1 << PD2));
    //*wheelDirectionPort_ |= (1 << PD3);
    OCR1A = (255 * 0)/100; 
    OCR1B = (255 * speed)/100;
    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
    TCCR1B = (1<<CS11) ;
    TCCR1C = 0;
}

void Wheels::turnLeft(uint8_t speed)
{
    *wheelDirectionPort_ &= ~((1 << PD3) | (1 << PD2));
   // *wheelDirectionPort_ |= (1 << PD2);
    OCR1A = (255 * speed)/100;
    OCR1B = (255 * 0)/100;
    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
    TCCR1B = (1<<CS11) ;
    TCCR1C = 0;
}

void Wheels::ajusterRight(uint8_t speed)
{
    OCR1A = (255 * speed )/100;
    OCR1B = (255 * speed)/120;
    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
    TCCR1B = (1<<CS11) ;
    TCCR1C = 0;
}

void Wheels::ajusterLeft(uint8_t speed)
{
    OCR1A = (255 * speed)/120;
    OCR1B = (255 * speed)/100;
    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
    TCCR1B = (1<<CS11) ;
    TCCR1C = 0;
}

void Wheels::backRight(uint8_t speed)
{
    *wheelDirectionPort_ |= ((1 << PD3) | (1 << PD2));
    OCR1A = (255 * speed)/100;
    OCR1B = (255 * 0)/100;
    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
    TCCR1B = (1<<CS11) ;
    TCCR1C = 0;
}

void Wheels::backLeft(uint8_t speed)
{
    *wheelDirectionPort_ |= ((1 << PD3) | (1 << PD2));
    OCR1B = (255 * speed)/100;
    OCR1A = (255 * 0)/100;
    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
    TCCR1B = (1<<CS11) ;
    TCCR1C = 0;
}

void Wheels::pivot(uint8_t speed)
{
    *wheelDirectionPort_ &= ~(1 << PD2);
    *wheelDirectionPort_ |= (1 << PD3);
    OCR1A = (255 * speed)/100;
    OCR1B = (255 * speed)/100;
    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
    TCCR1B = (1<<CS11) ;
    TCCR1C = 0;
}

void Wheels::pivot2(uint8_t speed)
{
    *wheelDirectionPort_ &= ~(1 << PD2);
    *wheelDirectionPort_ |= (1 << PD3);
    OCR1A = (255 * speed)/100;
    OCR1B = (255 * speed*1.15)/100;
    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
    TCCR1B = (1<<CS11) ;
    TCCR1C = 0;
}

void Wheels::ajustementPivot(uint8_t speed)
{
    *wheelDirectionPort_ &= ~(1 << PD2);
    *wheelDirectionPort_ |= (1 << PD3);
    OCR1A = (255 * speed)/100;
    OCR1B = (255 * speed)/100;
    TCCR1A = (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) ;
    TCCR1B = (1<<CS11) ;
    TCCR1C = 0;
}

void Wheels::unblock() // Les unblocks pourraient etre places dans classe Wheels
{
    moveForward(100);
    _delay_ms(200);
}

void Wheels::unblockP()
{
    pivot(100);
    _delay_ms(200);
}

void Wheels::unblockB()
{
    moveBackward(100);
    _delay_ms(200);
}

void Wheels::unblockR()
{
    turnRight(100);
    _delay_ms(200);
}

void Wheels::unblockL()
{
    turnLeft(100);
    _delay_ms(200);
}

void Wheels::stop()
{
    *wheelDirectionPort_ &= ~((1 << PD2) | (1 << PD3));
    OCR1A = 0;
    OCR1B = 0;
}

