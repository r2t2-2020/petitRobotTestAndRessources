//
// Created by gozlanp on 26/05/2021.
//

#ifndef TEST_ALLCOMPONANTS_ENCODERPERSO_H
#define TEST_ALLCOMPONANTS_ENCODERPERSO_H

// Encoder
Encoder encoderLeft(18, 19);
Encoder encoderRight(2, 3);
volatile long posLeft = 0;
volatile long posRight = 0;
volatile long commandLeft = -9999;
volatile long commandRight = -9999;

void encoderReadLeft(){
    if(encoderLeft.read() >= commandLeft){
        detachInterrupt(digitalPinToInterrupt(18));
        stopLeft();
    }
}

void encoderReadRight(){
    if(encoderRight.read() >= commandRight){
        detachInterrupt(digitalPinToInterrupt(2));
        stopRight();
    }
}

void Forward(long nbImpulsion)
{
    encoderLeft.write(0);
    encoderRight.write(0);
    commandLeft = nbImpulsion;
    commandRight = nbImpulsion;
    attachInterrupt(digitalPinToInterrupt(18), encoderReadLeft, CHANGE);
    attachInterrupt(digitalPinToInterrupt(2), encoderReadRight, CHANGE);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA,vitesseENA);
    analogWrite(ENB,vitesseENB);
}

/*#include <Arduino.h>
#include <Servo.h>
#include <SharpIR.h>
#include <MsTimer2.h>
#include <ServoPerso.h>
#include <Encoder.h>
#include "MotorsPerso.h"
#include "TelemetresPerso.h"*/

#endif //TEST_ALLCOMPONANTS_ENCODERPERSO_H
