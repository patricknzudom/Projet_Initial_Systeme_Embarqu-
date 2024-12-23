#ifndef CAPTEURDISTANCE_H
#define CAPTEURDISTANCE_H

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "Can.h"

#include "interfaces/utils.hpp"

#include "interfaces/emun/ModeRobot.hpp"
#include "interfaces/consts_lib.hpp"

class CapteurDistance
{
public:
	CapteurDistance(Register mode, uint8_t pinCapteur1, uint8_t pinCapteur2); // Constructeur CapteurDistance

	CapteurDistance(); // Constructeur par d�faut

	~CapteurDistance() = default;

	uint16_t lireValeur(); // retourne la valeur d'une seule lecture de distance

	uint16_t getDistance(); // retourne la moyenne de plusieurs lectures de distance

private:
	can convertisseur = can();
	Register mode_; // initialisation des I/O du port
	uint8_t pinCapteur1_;
	uint8_t pinCapteur2_;
};

#endif // CAPTEUR_DISTANCE_H