/*
 * Fichier: Debug.hpp
 *
 * Description:
 * Définit la classe Debug pour activer ou exclure les logs de débogage
 * via UART, utilisable avec `make debug`.
 * 
 * Identifications mat�rielles :
 * - Microcontr�leur : ATmega324PA
 */

#ifndef DEBUG_HPP
#define DEBUG_HPP

#include "Communication.hpp" // Assurez-vous que ce chemin est correct.

// Macro pour la facilitation du débogage.
#ifdef DEBUG
    #define DEBUG_MSG(msg) Debug::print(msg)
#else
    #define DEBUG_MSG(msg) do {} while (0) // Code mort si DEBUG n'est pas défini.
#endif

// Classe Debug pour la gestion des messages de débogage.
class Debug {
public:
    // Méthode pour afficher un message dans le terminal en mode débogage.
    static void print(const char* msg);

    static void printf(uint16_t number);
};

#endif // DEBUG_HPP
