#ifndef RS232Robot1_H
#define RS232Robot1_H

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "Can.h"
#include "Communication.hpp"
//#include "Timer.hpp"

#include "interfaces/utils.hpp"

#include "interfaces/consts_lib.hpp"

class Rs232Robot1
{
public:
	
	Rs232Robot1();

	~Rs232Robot1() = default;


	void envoiDessin(uint16_t posTop[], uint16_t lSegmentsTop[], uint16_t posBot[], uint16_t lSegmentBot[]);


	void setPosInitiale(uint8_t posInitiale){
		posInitiale_ = posInitiale;
	}

	void setCounter(uint8_t counter){
		counter_ = counter;
	}

private:
	Communication communication;

	uint8_t posInitiale_ = 0;
	
	uint8_t counter_ = 0;

	//Timer timer_(0);
};

#endif