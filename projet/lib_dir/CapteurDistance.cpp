#include "CapteurDistance.hpp"


 CapteurDistance::CapteurDistance(Register mode, uint8_t pinCapteur1, uint8_t pinCapteur2) : mode_(mode), pinCapteur1_(pinCapteur1), pinCapteur2_(pinCapteur2)
 {
     clearRegisterBits(mode_, pinCapteur1_);
     clearRegisterBits(mode_, pinCapteur2_);
 }

CapteurDistance::CapteurDistance(){}

uint16_t CapteurDistance::lireValeur() //114
{
	uint16_t valeurLue = convertisseur.lecture(A2_POSITION);
	return valeurLue;
}

uint16_t CapteurDistance::getDistance() //30
{
    uint16_t distanceSum = 0;

    //bcp de lectures
    for (uint8_t i = 0; i < NOMBRE_LECTURE; ++i)
        distanceSum += (uint16_t)convertisseur.lecture(A2_POSITION) >> 2;
    return distanceSum / NOMBRE_LECTURE;
}