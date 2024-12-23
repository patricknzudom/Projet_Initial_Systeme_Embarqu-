/*
* Fichier: utils.hpp
*
* Description: 
* Ce fichier contient des racoursis pour activer ou desactiver certains bits de registres
*/

#ifndef UTILS_H
#define UTILS_H
#define F_CPU 8000000UL
#include <avr/io.h>

/// Type défini pour représenter un registre AVR.
typedef volatile uint8_t *Register;


inline void setRegisterBits(Register avrRegister, const uint8_t bit)
{
    *avrRegister |= _BV(bit);
}

inline void clearRegisterBits(Register avrRegister, const uint8_t bit)
{
    *avrRegister &= ~_BV(bit);
}

#endif