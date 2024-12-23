/*
 * Fichier: Button.cpp
 *
 * Description:
 * Ce fichier implemente les methodes de la classe button pour l'utiliser avec des
 * interruptions ou avec scrutations.
 * 
 * Identifications matérielles :
 * - Microcontrôleur : ATmega324PA
 */
#include "Button.hpp" 



Button::Button(Register mode, Register pin, uint8_t pinNumber, const ButtonMode& buttonMode) : pin_(pin), buttonMode_(buttonMode), pinNumber_(pinNumber)
{
    clearRegisterBits(mode, pinNumber_);
}

bool Button::highSignal(uint8_t press) {                               // quand le signal est instable au debut de l'appuie du bouton
        if (buttonMode_ == ButtonMode::APPUIE){ // si pour mode appuie
            return (press == _BV(pinNumber_));
        }
        else {                                      // pour mode relache
            return (press != _BV(pinNumber_));
        }
    }  

bool Button::stableSignal(uint8_t press, uint8_t check) {                             // on s'assure que le signal est stable 
        return (press == check);
    }
    
bool Button::pressed()
{
    uint8_t press = *pin_ & _BV(pinNumber_);
    _delay_ms(DEBOUNCE_DELAY_MS);
    uint8_t check = *pin_ & _BV(pinNumber_);

    return (highSignal(press) && stableSignal(press, check));
}

Button::~Button() = default; 