#include "Rs232Robot1.hpp"
#include <util/delay.h>

uint8_t nIndex = 0;

Rs232Robot1::Rs232Robot1() {
    communication.initializeUART();
}

void Rs232Robot1::envoiDessin(uint16_t posTop[], uint16_t lSegmentsTop[], uint16_t posBot[], uint16_t lSegmentsBot[]){
    _delay_ms(5000);


    // REMPLACEMENT CARACTERE DU PARCOURS PAR CEUX DES SEGMENTS
    bool insertCharTop[53] = {false};
    int segmentLengthTop[53] = {0}; //Stockage de la longueur de chaque segment
    for (int indexSegmentTop = 0; indexSegmentTop < 3; indexSegmentTop++) {
        
        uint8_t posSegTop = (posTop[indexSegmentTop] * 53) / 100; // Convertit le pourcentage en indice
        if (posSegTop < 53) {
            insertCharTop[posSegTop] = true; // Marquez l'indice pour insérer le caractère
            segmentLengthTop[posSegTop] = (lSegmentsTop[indexSegmentTop]/2);
        }
    }

    // REMPLACEMENT CARACTERE PARCOURS BAS
    bool insertCharBot[53] = {false};
    int segmentLengthBot[53] = {0}; //Stockage de la longueur de chaque segment pour la partie basse
    for (int indexSegmentBot = 0; indexSegmentBot < 3; indexSegmentBot++) {
        uint8_t posSegBot = (posBot[indexSegmentBot] * 53) / 100; // Convertit le pourcentage en indice pour la partie basse
        if (posSegBot < 53) {
            insertCharBot[posSegBot] = true; // Marquez l'indice pour insérer le caractère pour la partie basse
            segmentLengthBot[posSegBot] = (lSegmentsBot[indexSegmentBot]/2); // À ajuster si nécessaire
        }
    }

    communication.printf("\xE2\x94\x8C");
    for(uint8_t i = 0; i < 99; i++){
        communication.printf("\xE2\x94\x80");
    }
    communication.printf("\xE2\x94\x90\n");

    
    for (uint8_t i = 0; i < 3; i++){
        communication.printf("\xE2\x94\x82");
        for(uint8_t i = 0; i < 99; i++){
            communication.printf(" ");
        }
        communication.printf("\xE2\x94\x82\n");
    }

    //debut boite
    communication.printf("\xE2\x94\x82");
    for (uint8_t i = 0; i < 4; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x8F");
    for (uint8_t i = 0; i < 20; i++){
        communication.printf("\xE2\x94\x81");
    }
    communication.printf("\xE2\x94\x93");

    for (uint8_t i = 0; i < 73; i++){
        communication.printf(" ");
    }

    communication.printf("\xE2\x94\x82\n");

    //2e ligne boite

    communication.printf("\xE2\x94\x82");
    for (uint8_t i = 0; i < 4; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");
    for (uint8_t i = 0; i < 20; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");

    for (uint8_t i = 0; i < 73; i++){
        communication.printf(" ");
    }

    communication.printf("\xE2\x94\x82\n");


    //3e ligne boite
    //debut cadre

    communication.printf("\xE2\x94\x82");
    for (uint8_t i = 0; i < 4; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");
    for (uint8_t i = 0; i < 20; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");


    for (uint8_t i = 0; i < 7; i++){
        communication.printf(" ");
    }

    // DEBUT PARTIE SURPERIEUR PARCOURS ET INSERTION SEGMENT
    communication.printf("\xE2\x95\x94");
    for (uint8_t i = 0; i < 53; i++) {
        if (insertCharTop[i]) {
            communication.printf("\xE2\x95\xA6"); // Insère le caractère spécial à l'indice marqué
        } else {
            communication.printf("\xE2\x95\x90"); // Dessine le caractère de ligne horizontale
        }
    }
    communication.printf("\xE2\x95\x97");

    for (uint8_t i = 0; i < 11; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x82\n");

    //2e ligne cadre
    // debut robot // 5 horizontale

    uint8_t i = 0;

    communication.printf("\xE2\x94\x82");
    for (uint8_t j = 0; j < 4; j++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");
    
    if(((posInitiale_ == 2) && (counter_ < 100)) || ((posInitiale_ == 1) && (counter_ > 75))){ //en haut
        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }

        communication.printf("\u2571");

        communication.printf("\u2500");
        communication.printf("\u2500");

        communication.printf("\u2572");

        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }
    } else {
        for (uint8_t j = 0; j < 20; j++){
            communication.printf(" ");
        }
    }

    communication.printf("\xE2\x94\x83");

    for (uint8_t j = 0; j < 7; j++){
        communication.printf(" ");
    }

    // SUITE INSERTION SEGMENT
    communication.printf("\xE2\x95\x91");
    for (uint8_t j = 0; j < 53; j++){
        if (insertCharTop[j] && i < segmentLengthTop[j]) {
            communication.printf("\xE2\x95\x91"); // Insère le caractère spécial à l'indice marqué
        } else {
            communication.printf(" "); // Dessine le caractère de ligne horizontale
        }
    }
    communication.printf("\xE2\x95\x91");

    for (uint8_t i = 0; i < 11; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x82\n");

    //2e ligne robot OU 3e ligne cadre

    i = 1;

    communication.printf("\xE2\x94\x82");
    for (uint8_t j = 0; j < 4; j++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");
    
    if((posInitiale_ == 2) && (counter_ < 100)){ //en haut vers arriere
        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }

        communication.printf("\u2502");

        communication.printf(" ");
        communication.printf(" ");

        communication.printf("\u2502");

        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }
    } else if (((posInitiale_ == 1) && (counter_ > 75))){ // en haut vers devant
            for (uint8_t i = 0; i < 8; i++){
                communication.printf(" ");
            }

            communication.printf("\u256C");

            communication.printf(" ");
            communication.printf(" ");

            communication.printf("\u256C");

            for (uint8_t i = 0; i < 8; i++){
                communication.printf(" ");
            }
        } else{
            for (uint8_t j = 0; j < 20; j++){
                communication.printf(" ");
        }
    }

    communication.printf("\xE2\x94\x83");

    for (uint8_t j = 0; j < 7; j++){
        communication.printf(" ");
    }

    // SUITE INSERTION SEGMENT
    communication.printf("\xE2\x95\x91");
    for (uint8_t j = 0; j < 53; j++){
        if (insertCharTop[j] && i < segmentLengthTop[j]) {
            communication.printf("\xE2\x95\x91"); // Insère le caractère spécial à l'indice marqué
        } else {
            communication.printf(" "); // Dessine le caractère de ligne horizontale
        }
    }
    communication.printf("\xE2\x95\x91");

    for (uint8_t i = 0; i < 11; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x82\n");

    // 3e ligne robot OU 4e ligne cadre

    i = 2;

    communication.printf("\xE2\x94\x82");
    for (uint8_t j = 0; j < 4; j++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");
    
    if((posInitiale_ == 2) && (counter_ < 100)){ //en haut vers arriere
        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }

        communication.printf("\u256C");

        communication.printf(" ");
        communication.printf(" ");

        communication.printf("\u256C");

        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }
    } else if (((posInitiale_ == 1) && (counter_ > 75))){ // en haut vers devant
            for (uint8_t i = 0; i < 8; i++){
                communication.printf(" ");
            }

            communication.printf("\u2502");

            communication.printf(" ");
            communication.printf(" ");

            communication.printf("\u2502");

            for (uint8_t i = 0; i < 8; i++){
                communication.printf(" ");
            }
        } else{
            for (uint8_t j = 0; j < 20; j++){
                communication.printf(" ");
        }
    }

    communication.printf("\xE2\x94\x83");

    for (uint8_t j = 0; j < 7; j++){
        communication.printf(" ");
    }

    // SUITE INSERTION SEGMENT
    communication.printf("\xE2\x95\x91");
    for (uint8_t j = 0; j < 53; j++){
        if (insertCharTop[j] && i < segmentLengthTop[j]) {
            communication.printf("\xE2\x95\x91"); // Insère le caractère spécial à l'indice marqué
        } else {
            communication.printf(" "); // Dessine le caractère de ligne horizontale
        }
    }
    communication.printf("\xE2\x95\x91");

    for (uint8_t i = 0; i < 11; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x82\n");

    // 4e ligne robot OU 5e ligne cadre

    i = 3;

    communication.printf("\xE2\x94\x82");
    for (uint8_t j = 0; j < 4; j++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");
    
    if((posInitiale_ == 2) && (counter_ < 100)){ //en haut vers arriere
        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }

        communication.printf("\u2572");

        communication.printf("\u2500");
        communication.printf("\u2500");

        communication.printf("\u2571");

        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }
    } else if (((posInitiale_ == 1) && (counter_ > 75))){ // en haut vers devant
            for (uint8_t i = 0; i < 8; i++){
                communication.printf(" ");
            }

            communication.printf("\u2572");

            communication.printf("\u2500");
            communication.printf("\u2500");

            communication.printf("\u2571");

            for (uint8_t i = 0; i < 8; i++){
                communication.printf(" ");
            }
        } else{
            for (uint8_t j = 0; j < 20; j++){
                communication.printf(" ");
        }
    }

    communication.printf("\xE2\x94\x83");

    for (uint8_t j = 0; j < 7; j++){
        communication.printf(" ");
    }

    // SUITE INSERTION SEGMENT
    communication.printf("\xE2\x95\x91");
    for (uint8_t j = 0; j < 53; j++){
        if (insertCharTop[j] && i < segmentLengthTop[j]) {
            communication.printf("\xE2\x95\x91"); // Insère le caractère spécial à l'indice marqué
        } else {
            communication.printf(" "); // Dessine le caractère de ligne horizontale
        }
    }
    communication.printf("\xE2\x95\x91");

    for (uint8_t i = 0; i < 11; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x82\n");    

    // 6e ligne cadre

    i = 4;

    communication.printf("\xE2\x94\x82");
    for (uint8_t j = 0; j < 4; j++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");
    
    for (uint8_t j = 0; j < 20; j++){
        communication.printf(" ");
    }

    communication.printf("\xE2\x94\x83");

    for (uint8_t j = 0; j < 7; j++){
        communication.printf(" ");
    }

    // SUITE INSERTION SEGMENT
    communication.printf("\xE2\x95\x91");
    for (uint8_t j = 0; j < 53; j++){
        if (insertCharTop[j] && i < segmentLengthTop[j]) {
            communication.printf("\xE2\x95\x91"); // Insère le caractère spécial à l'indice marqué
        } else {
            communication.printf(" "); // Dessine le caractère de ligne horizontale
        }
    }
    communication.printf("\xE2\x95\x91");

    for (uint8_t i = 0; i < 11; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x82\n");

    //debut ouverture

    for (uint8_t i = 0; i < 2; i++){
        communication.printf("\xE2\x94\x82");
        for (uint8_t i = 0; i < 4; i++){
            communication.printf(" ");
        }
        communication.printf("\xE2\x94\x83");
        for (uint8_t i = 0; i < 20; i++){
            communication.printf(" ");
        }
        communication.printf(" ");


        for (uint8_t i = 0; i < 7; i++){
            communication.printf(" ");
        }
        communication.printf("\xE2\x95\x91");

        for (uint8_t i = 0; i < 53; i++){
            communication.printf(" ");
        }
        communication.printf("\xE2\x95\x91");
    
        for (uint8_t i = 0; i < 11; i++){
            communication.printf(" ");
        }
        communication.printf("\xE2\x94\x82\n");
    }

    //ligne ouverture

    communication.printf("\xE2\x94\x82");
    for (uint8_t i = 0; i < 4; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");
    for (uint8_t i = 0; i < 23; i++){
        communication.printf(" ");
    }

    for (uint8_t i = 0; i < 5; i++){
        communication.printf("\xE2\x95\x90"); // Fin Parcours robot
    }
    communication.printf("\xE2\x95\xA3");

    for (uint8_t i = 0; i < 53; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x95\x91");

    for (uint8_t i = 0; i < 11; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x82\n");

    //fin ouverture

    for (uint8_t i = 0; i < 2; i++){
        communication.printf("\xE2\x94\x82");
        for (uint8_t i = 0; i < 4; i++){
            communication.printf(" ");
        }
        communication.printf("\xE2\x94\x83");
        for (uint8_t i = 0; i < 20; i++){
            communication.printf(" ");
        }
        communication.printf(" ");


        for (uint8_t i = 0; i < 7; i++){
            communication.printf(" ");
        }
        communication.printf("\xE2\x95\x91");

        for (uint8_t i = 0; i < 53; i++){
            communication.printf(" ");
        }
        communication.printf("\xE2\x95\x91");
    
        for (uint8_t i = 0; i < 11; i++){
            communication.printf(" ");
        }
        communication.printf("\xE2\x94\x82\n");
    }

    //debut robot OU 1e vide
    i = 0;
    communication.printf("\xE2\x94\x82");
    for (uint8_t i = 0; i < 4; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");


    if(((posInitiale_ == 2) && (counter_ > 100)) || ((posInitiale_ == 1) && (counter_ < 75))){ //en bas
        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }

        communication.printf("\u2571");

        communication.printf("\u2500");
        communication.printf("\u2500");

        communication.printf("\u2572");

        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }
    } else {
        for (uint8_t j = 0; j < 20; j++){
            communication.printf(" ");
        }
    }

    communication.printf("\xE2\x94\x83");


    for (uint8_t i = 0; i < 7; i++){
        communication.printf(" ");
    }

    // INSERTION SEGMENT BAS
    communication.printf("\xE2\x95\x91");
    for (uint8_t j = 0; j < 53; j++){
        if (insertCharBot[j] && (5 - i) <= segmentLengthBot[j]) {
                communication.printf("\xE2\x95\x91"); // Insère ║ à l'indice marqué
        } else {
            communication.printf(" "); // Insere espace
        }
    }
    communication.printf("\xE2\x95\x91");

    for (uint8_t i = 0; i < 11; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x82\n");


    //2e ligne robot OU 2e vide

    i = 1;
    communication.printf("\xE2\x94\x82");
    for (uint8_t i = 0; i < 4; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");


    if((posInitiale_ == 2) && (counter_ > 100)){ //en bas vers arriere
        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }

        communication.printf("\u256C");

        communication.printf(" ");
        communication.printf(" ");

        communication.printf("\u256C");

        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }
    } else if (((posInitiale_ == 1) && (counter_ < 75))){ // en bas vers devant
            for (uint8_t i = 0; i < 8; i++){
                communication.printf(" ");
            }

            communication.printf("\u2502");

            communication.printf(" ");
            communication.printf(" ");

            communication.printf("\u2502");

            for (uint8_t i = 0; i < 8; i++){
                communication.printf(" ");
            }
        } else{
            for (uint8_t j = 0; j < 20; j++){
                communication.printf(" ");
        }
    }

    communication.printf("\xE2\x94\x83");


    for (uint8_t i = 0; i < 7; i++){
        communication.printf(" ");
    }

    // INSERTION SEGMENT BAS
    communication.printf("\xE2\x95\x91");
    for (uint8_t j = 0; j < 53; j++){
        if (insertCharBot[j] && (5 - i) <= segmentLengthBot[j]) {
                communication.printf("\xE2\x95\x91"); // Insère ║ à l'indice marqué
        } else {
            communication.printf(" "); // Insere espace
        }
    }
    communication.printf("\xE2\x95\x91");

    for (uint8_t i = 0; i < 11; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x82\n");

    //3e ligne robot OU 3e vide

    i = 2;

    communication.printf("\xE2\x94\x82");
    for (uint8_t i = 0; i < 4; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");


    if((posInitiale_ == 2) && (counter_ > 100)){ //en bas vers arriere
        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }

        communication.printf("\u2502");

        communication.printf(" ");
        communication.printf(" ");

        communication.printf("\u2502");

        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }
    } else if (((posInitiale_ == 1) && (counter_ < 75))){ // en bas vers devant
            for (uint8_t i = 0; i < 8; i++){
                communication.printf(" ");
            }

            communication.printf("\u256C");

            communication.printf(" ");
            communication.printf(" ");

            communication.printf("\u256C");

            for (uint8_t i = 0; i < 8; i++){
                communication.printf(" ");
            }
        } else{
            for (uint8_t j = 0; j < 20; j++){
                communication.printf(" ");
        }
    }

    communication.printf("\xE2\x94\x83");


    for (uint8_t i = 0; i < 7; i++){
        communication.printf(" ");
    }

    // INSERTION SEGMENT BAS
    communication.printf("\xE2\x95\x91");
    for (uint8_t j = 0; j < 53; j++){
        if (insertCharBot[j] && (5 - i) <= segmentLengthBot[j]) {
                communication.printf("\xE2\x95\x91"); // Insère ║ à l'indice marqué
        } else {
            communication.printf(" "); // Insere espace
        }
    }
    communication.printf("\xE2\x95\x91");

    for (uint8_t i = 0; i < 11; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x82\n");

    //presque fin cadre
    //fin robot OU 4e vide

    i = 3;

    communication.printf("\xE2\x94\x82");
    for (uint8_t i = 0; i < 4; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");


    if(((posInitiale_ == 2) && (counter_ > 100)) || ((posInitiale_ == 1) && (counter_ < 75))){ //en bas
        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }

        communication.printf("\u2572");

        communication.printf("\u2500");
        communication.printf("\u2500");

        communication.printf("\u2571");

        for (uint8_t i = 0; i < 8; i++){
            communication.printf(" ");
        }
    } else {
        for (uint8_t j = 0; j < 20; j++){
            communication.printf(" ");
        }
    }

    communication.printf("\xE2\x94\x83");


    for (uint8_t i = 0; i < 7; i++){
        communication.printf(" ");
    }
    
    // INSERTION SEGMENT BAS
    communication.printf("\xE2\x95\x91");
    for (uint8_t j = 0; j < 53; j++){
        if (insertCharBot[j] && (5 - i) <= segmentLengthBot[j]) {
                communication.printf("\xE2\x95\x91"); // Insère ║ à l'indice marqué
        } else {
            communication.printf(" "); // Insere espace
        }
    }
    communication.printf("\xE2\x95\x91");

    for (uint8_t i = 0; i < 11; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x82\n");

    //fin cadre

    i = 4;

    communication.printf("\xE2\x94\x82");
    for (uint8_t i = 0; i < 4; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");
    for (uint8_t i = 0; i < 20; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");


    for (uint8_t i = 0; i < 7; i++){
        communication.printf(" ");
    }
    
    // INSERTION SEGMENT BAS
    communication.printf("\xE2\x95\x91");
    for (uint8_t j = 0; j < 53; j++){
        if (insertCharBot[j] && (5 - i) <= segmentLengthBot[j]) {
                communication.printf("\xE2\x95\x91"); // Insère ║ à l'indice marqué
        } else {
            communication.printf(" "); // Insere espace
        }
    }
    communication.printf("\xE2\x95\x91");

    for (uint8_t i = 0; i < 11; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x82\n");

    // LIGNE BAS 
    communication.printf("\xE2\x94\x82");
    for (uint8_t i = 0; i < 4; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");
    for (uint8_t i = 0; i < 20; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");


    for (uint8_t i = 0; i < 7; i++){
        communication.printf(" ");
    }

    // LIGNE PARCOURS BAS ET INSERTION POSITION SEGMENT
    communication.printf("\xE2\x95\x9A");
    nIndex = 0;
    for (uint8_t i = 0; i < 53; i++) {
        if (insertCharBot[i]) {
            communication.printf("\xE2\x95\xA9"); // Insère ╩ à l'indice marqué
        } else {
            communication.printf("\xE2\x95\x90"); // Dessine ligne verticale
        }
    }
    communication.printf("\xE2\x95\x9D");

    for (uint8_t i = 0; i < 11; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x82\n");


    //presque fin boite

    communication.printf("\xE2\x94\x82");
    for (uint8_t i = 0; i < 4; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");
    for (uint8_t i = 0; i < 20; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x83");

    for (uint8_t i = 0; i < 73; i++){
        communication.printf(" ");
    }

    communication.printf("\xE2\x94\x82\n");

    // fin boite

    communication.printf("\xE2\x94\x82");
    for (uint8_t i = 0; i < 4; i++){
        communication.printf(" ");
    }
    communication.printf("\xE2\x94\x97");
    for (uint8_t i = 0; i < 20; i++){
        communication.printf("\xE2\x94\x81");
    }
    communication.printf("\xE2\x94\x9B");

    for (uint8_t i = 0; i < 73; i++){
        communication.printf(" ");
    }

    communication.printf("\xE2\x94\x82\n");

    //avant fin table

    for (uint8_t i = 0; i < 3; i++){
        communication.printf("\xE2\x94\x82");
        for(uint8_t i = 0; i < 99; i++){
            communication.printf(" ");
        }
        communication.printf("\xE2\x94\x82\n");
    }

    //fin table

    communication.printf("\xE2\x94\x94");
    for(uint8_t i = 0; i < 99; i++){
        communication.printf("\xE2\x94\x80");
    }
    communication.printf("\xE2\x94\x98\n");

    communication.printf("Produit par: Jean-Michel\n");
}