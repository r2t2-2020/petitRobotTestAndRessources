//
// Created by gozlanp on 26/05/2021.
//
#include <Servo.h>
#include <SharpIR.h>
#include <MsTimer2.h>
#include <ServoPerso.h>
#include <Encoder.h>
#include "MotorsPerso.h"
#include "TelemetresPerso.h"
#include "EncoderPerso.h"
#include "TirettePerso.h"

#ifndef TEST_ALLCOMPONANTS_STRATEGIES_H
#define TEST_ALLCOMPONANTS_STRATEGIES_H

void manoeuvreDrapeaux1(){
    Forward();
    testServo();
    delay(500);
    arret();
}

void strategie1(){ // recoit char cote
    Turn_left();
    delay(1000); // pour faire un tour de 90% degrés

    arret();
    delay(500);

    Forward(2000);
    //Forward();
    //delay(); pour parcourir la distance jusqu'a l'angle

    Turn_right();
    delay(1000); // pour faire un tour de 90% degrés

    // ON ATTEINT ICI LANGLE ET ON COMMENCE LA MANOEUVRE POUR LEVER LES DRAPEAUX

    manoeuvreDrapeaux1();
}

#endif //TEST_ALLCOMPONANTS_STRATEGIES_H
