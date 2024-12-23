#ifndef RS232_H
#define RS232_H

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "Can.h"
#include "Communication.hpp"

#include "interfaces/utils.hpp"

#include "interfaces/consts_lib.hpp"

class Rs232
{
public:
	
	Rs232();

	~Rs232() = default;

	void envoiDessin(uint16_t posTop[], uint16_t lSegmentsTop[], uint16_t posBot[], uint16_t lSegmentsBot[], uint16_t nSegTop, uint16_t nSegBot);

private:
	Communication communication;
};

#endif