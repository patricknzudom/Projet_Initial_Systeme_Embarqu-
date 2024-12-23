#ifndef BYTECODE_H
#define BYTECODE_H
#include "Communication.hpp"
#include "Memoire_24.h"
#include "Led.hpp"
#include "Wheels.hpp"


class Bytecode
{
public:
    Bytecode() = default;
    ~Bytecode() = default;
    uint16_t bytecodeInitUART();
    void ecritureBytecode();
private:
    Communication uart = Communication();
    Led led = Led(&PORTA, &DDRA, PA0, PA1);
    Memoire24CXXX memory = Memoire24CXXX();
    uint16_t adresse_ = 0x0000;
    uint16_t bytecode = 0x0000;
};

#endif