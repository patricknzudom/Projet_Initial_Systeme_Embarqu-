/*
 * Fichier: Communication.h
 *
 * Description:
 * La classe Communication permet de controller la communication entre le microcontroleur
 * et le p�riph�rique externe avec UART.
 *
 * Identifications mat�rielles :
 * - Microcontr�leur : ATmega324PA
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "interfaces/utils.hpp"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "Memoire_24.h"

class Communication
{
public:
    Communication();

    static void initializeUART();

    static void transmissionUART(uint8_t data);

    static uint8_t readUART();

    static void sendSerialInteger(int16_t number);

    static void sendSerialString(const uint8_t data[], uint8_t length);

    static void printf(const char format[], ...);
};

#endif
