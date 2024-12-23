/*
 * Fichier: Communication.cpp
 *
 * Description:
 * Ce fichier implemente les methodes de la classe Communication.
 *
 * Identifications mat�rielles :
 * - Microcontr�leur : ATmega324PA
 */
#include "Communication.hpp"

Communication::Communication() {
    initializeUART();
}

void Communication::initializeUART()
{
    // Configuration du d�bit de communication
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // Activation de la transmission et r�ception
    UCSR0A |= (1 << MPCM0);
    setRegisterBits(&UCSR0B, RXEN0);
    setRegisterBits(&UCSR0B, TXEN0);
    // Configuration des bits de donn�es et de la parit� (8 bits de donn�es, pas de parit�)
    setRegisterBits(&UCSR0C, UCSZ00);
    setRegisterBits(&UCSR0C, UCSZ01);
}

void Communication::transmissionUART(uint8_t data)
{
    // Attend que la file de transmission soit vide avant d'envoyer les donn�es
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = data;
}

uint8_t Communication::readUART()
{
    while (!(UCSR0A & (1 << RXC0)))
        ;
    // retouner la donn�e lue
    return UDR0;
}

void Communication::sendSerialString(const uint8_t data[], uint8_t length)
{
    for (uint32_t i = 0; i < length; i++)
    {
        transmissionUART(data[i]);
    }
}

void Communication::sendSerialInteger(int16_t number)
{
    uint8_t buffer[255]; // Un tampon pour stocker la chaîne formatée
    sprintf((char *)buffer, "%d", number);
    sendSerialString(buffer, strlen((char *)buffer));
}

void Communication::printf(const char format[], ...)
{
    va_list args;
    va_start(args, format);
    uint8_t buffer[255]; // Un tampon pour stocker la chaîne formatée

    vsnprintf((char *)buffer, sizeof(buffer), format, args);
    va_end(args);

    sendSerialString(buffer, strlen((char *)buffer));
}
