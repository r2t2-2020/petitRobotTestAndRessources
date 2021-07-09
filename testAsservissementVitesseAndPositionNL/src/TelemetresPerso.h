//
// Created by gozlanp on 23/06/2021.
//

#ifndef TESTASSERVISSEMENTVITESSEANDPOSITIONNL_TELEMETRESPERSO_H
#define TESTASSERVISSEMENTVITESSEANDPOSITIONNL_TELEMETRESPERSO_H

#include <digitalWriteFast.h>

bool isObstacle = false;

const unsigned long dureeAntiRebondTel = 20;
unsigned long dateDernierChangementTel = 0;

bool isTelsAble = false;

void ableTels(){
    isTelsAble = true;
}

void disableTels(){
    isTelsAble = false;
}

// pins 50 à 53 dans le registre == 0b 0 0 0 0 50 51 52 53; choisir les bons bits à changer d'état
// telemetres à 1 quand il n'y a pas d'obstacle

/*
void disableTelemetresArriere(){ //52 53
    PCMSK0 &= 0b00001100;
}

void disableTelemetresAvant(){ //50 51
    PCMSK0 &= 0b00000011;
}

void enableTelemetresArriere(){ //52 53
    PCMSK0 |= 0b00000011;
}

void enableTelemetresAvant(){ //50 51
    PCMSK0 |= 0b00001100;
}
void disableTels(){
    PCMSK0 = 0b00000000;
}

void ableTels(){
    PCMSK0 = 0b00001111;
}
 */

bool detectObstacle_AV(){
    return digitalReadFast(50) == 0 || digitalReadFast(51) == 0;
}

bool detectObstacle_AR(){
    return digitalReadFast(52) == 0 || digitalReadFast(53) == 0;
}

bool detectObstacle(){
    return detectObstacle_AR() || detectObstacle_AV();
}

void testTelAvantInfini(){
    while(1){
        Serial.print("gauche: ");
        Serial.println(digitalRead(50));

        Serial.print("droite: ");
        Serial.println(digitalRead(51));

        delay(500);
    }
}

void testAllTelemetres(){
    while(1) {
        Serial.print(detectObstacle_AV());
        Serial.print(" : ");
        Serial.println(detectObstacle_AR());
    }
}

void testAllTelemetresBool(){
    while(1) {
        Serial.println(isObstacle);
        isObstacle = false;
        delay(1000);
    }
}

const int motG_IN1_tel = 8;
const int motG_IN2_tel = 4;
const int pinPowerG_tel  = 7;

const int motD_IN3_tel = 12;
const int motD_IN4_tel = 11;
const int pinPowerD_tel  = 5;

int cptVerifObstacle = 0;

//ISR(PCINT0_vect){
    /*
    unsigned long date = millis();
    cptVerifObstacle++;
    if ((date - dateDernierChangementTel) > dureeAntiRebondTel) {
        digitalWrite(motD_IN3_tel, HIGH);
        digitalWrite(motD_IN4_tel, HIGH);
        analogWrite(pinPowerD_tel, 0);

        digitalWrite(motG_IN1_tel, HIGH);
        digitalWrite(motG_IN2_tel, HIGH);
        analogWrite(pinPowerG_tel, 0);
        isObstacle = true;
        dateDernierChangementTel = date;
   // }
     */

    /*
        if(digitalRead(53) == 0){
            //Serial.println("je suis le pin 53, arriere droite");
            isObstacle = true;
            //isObstacle = isObstacle ? false : true; // isObstacle_AR
            //Serial.println("isObstacle_AR : " + isObstacle_AR);
        }

        if(digitalRead(52) == 0){
            //Serial.println("je suis le pin 52, arriere gauche");
            isObstacle = true;
            //isObstacle = isObstacle ? false : true; // isObstacle_AR
            //Serial.println("isObstacle_AR : " + isObstacle_AR);
        }

        if(digitalRead(51) == 0){
            //Serial.println("je suis le pin 51, avant droite");
            isObstacle = true;
            //isObstacle = isObstacle ? false : true; // isObstacle_AV
            //Serial.println("isObstacle_AV : " + isObstacle_AV);
        }

        if(digitalRead(50) == 0){
            //Serial.println("je suis le pin 50, avant gauche");
            isObstacle = true;
            //isObstacle = isObstacle ? false : true; // isObstacle_AV
            //Serial.println("isObstacle_AV : " + isObstacle_AV);
        }
    */



#endif //TESTASSERVISSEMENTVITESSEANDPOSITIONNL_TELEMETRESPERSO_H
