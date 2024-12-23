/*
 * Fichier: Debug.cpp
 *
 * Description:
 * Implémente la classe Debug pour le débogage via UART sur l'ATmega324PA,
 * facilitant le diagnostic et la vérification du programme.
 * 
 * Identifications matérielles :
 * - Microcontr�leur : ATmega324PA
 */

#include "Debug.hpp"
#include <string.h> // Pour strlen()

// Implémentation de Debug::print.
void Debug::print(const char* msg) {
    Communication comm; // Instance de Communication pour accéder à ses méthodes.
    
    // Étant donné que Communication::showMemory semble être la méthode désignée pour le débogage,
    // on pourrait l'utiliser ici. Cependant, les instructions ne clarifient pas son usage exact.
    // Donc, nous utilisons la méthode transmissionUART pour l'envoi de messages caractère par caractère.
    for(size_t i = 0; i < strlen(msg); ++i) {
        comm.transmissionUART(static_cast<uint8_t>(msg[i]));
    }
    // Envoyer un caractère de fin de ligne à la fin du message.
    comm.transmissionUART('\n');
}


void Debug::printf(uint16_t number)
{
    Communication::sendSerialInteger(number);
    Communication::transmissionUART('\n');
}

