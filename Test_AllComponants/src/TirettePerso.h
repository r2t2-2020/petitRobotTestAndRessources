//
// Created by gozlanp on 26/05/2021.
//

#ifndef TEST_ALLCOMPONANTS_TIRETTEPERSO_H
#define TEST_ALLCOMPONANTS_TIRETTEPERSO_H

const int pin_tirette = 4;
bool isTimerSet = false;

void finRun()
{
    Serial.println("fin du run");
    arret();
    while(1);

}


//dans le setup
//attachInterrupt(digitalPinToInterrupt(18), obstacleArriereGauche, FALLING);
//attachInterrupt(digitalPinToInterrupt(19), obstacleArriereDroit, FALLING);

//attachInterrupt(digitalPinToInterrupt(24), NoObstacleArriereGauche, RISING);
//attachInterrupt(digitalPinToInterrupt(20), NoObstacleArriereDroit, RISING);
/*#include <Arduino.h>
#include <Servo.h>
#include <SharpIR.h>
#include <MsTimer2.h>
#include <ServoPerso.h>
#include <Encoder.h>
#include "MotorsPerso.h"
#include "TelemetresPerso.h"
#include "EncoderPerso.h"*/

#endif //TEST_ALLCOMPONANTS_TIRETTEPERSO_H
