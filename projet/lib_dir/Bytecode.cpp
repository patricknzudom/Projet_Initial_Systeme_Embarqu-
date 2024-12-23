#include "Bytecode.hpp"

static const uint8_t BIT_DECALAGE = 8;
static const uint8_t ADRESSE_ENLEVER = 2;
static const uint8_t DELAY_ECRITURE = 5; 

uint16_t Bytecode::bytecodeInitUART()
{

    uart.initializeUART();
    uint8_t dataInstructions = uart.readUART();
    uint8_t dataOperandes = uart.readUART();
    bytecode |= dataOperandes | (dataInstructions << BIT_DECALAGE) ;
    return bytecode;
}

void Bytecode::ecritureBytecode()
{
    uint16_t bytes = bytecodeInitUART();
    uint16_t data;
    while (adresse_ < (bytes - ADRESSE_ENLEVER))
    {
        data = uart.readUART();
        memory.ecriture(adresse_++, data);
        _delay_ms(DELAY_ECRITURE);   
    }
}