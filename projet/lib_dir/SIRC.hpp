#ifndef SIRC_H
#define SIRC_H

class SIRC {
public:
    SIRC(); // Constructeur
    void send(int command, int address); // Méthode pour envoyer un message

private:
    void burst38kHz(int duration_us);
    void sendBit(int bit);
    static const int START_BURST_DURATION = 2400;
    static const int BIT_1_DURATION = 1200;
    static const int BIT_0_DURATION = 600;
    static const int STANDARD_SPACE = 600;
};

#endif
