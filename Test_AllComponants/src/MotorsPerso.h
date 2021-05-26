//
// Created by gozlanp on 26/05/2021.
//

#ifndef TEST_ALLCOMPONANTS_MOTORSPERSO_H
#define TEST_ALLCOMPONANTS_MOTORSPERSO_H

/* Moteur Droite*/
const byte ENA=10; //PWM
const byte IN1=8; // Dir 1A
const byte IN2=9; // 2A

/* Moteur Gauche*/
const byte ENB=13; //PWM
const byte IN4=12; // Dir 1B
const byte IN3=11; // 2B

int vitesseENA = 80;
int vitesseENB = 80;

#include "../.pio/libdeps/megaatmega2560/Encoder/Encoder.h"
#include "../.pio/libdeps/megaatmega2560/SharpIR/src/SharpIR.h"

void arret()
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4, HIGH);
}

void stopRight()
{
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, HIGH);
}

void stopLeft()
{
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, HIGH);
}

void Forward()
{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA,vitesseENA);
    analogWrite(ENB,vitesseENB);
}

void Backward()
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENA,vitesseENA);
    analogWrite(ENB,vitesseENB);
}

void moveBackwardLeft(){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA,vitesseENA);
}

void moveBackwardRight(){
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    analogWrite(ENB,vitesseENB);
}

void Turn_left()
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4, HIGH);
    analogWrite(ENA,vitesseENA);
}

void Turn_right()
{
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB,vitesseENB);
}

void testMoteurs(){
    Forward();
    delay(2000);
    arret();
    delay(1000);
    Backward();
    delay(2000);
    arret();
    delay(1000);
}

/*#include <Arduino.h>
#include <Servo.h>
#include <SharpIR.h>
#include <MsTimer2.h>
#include <ServoPerso.h>
#include <Encoder.h>*/

#endif //TEST_ALLCOMPONANTS_MOTORSPERSO_H
