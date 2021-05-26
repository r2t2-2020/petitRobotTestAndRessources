//
// Created by gozlanp on 26/05/2021.
//

#ifndef TEST_ALLCOMPONANTS_TELEMETRESPERSO_H
#define TEST_ALLCOMPONANTS_TELEMETRESPERSO_H

/*
orange 0
jaune 1
vert 2
bleu 3
*/

// lien pour telemetres IR https://www.instructables.com/How-to-Use-the-Sharp-IR-Sensor-GP2Y0A41SK0F-Arduin/

// Telemetres_IR_AV droite et gauche
SharpIR telAvG(SharpIR::GP2Y0A21YK0F, A0);
SharpIR telAvD(SharpIR::GP2Y0A21YK0F, A1);
int Dist_AvG;
int Dist_AvD;

// Telemetres_IR_AR droite et gauche
SharpIR telArG(SharpIR::GP2Y0A21YK0F, A2);
SharpIR telArD(SharpIR::GP2Y0A21YK0F, A3);
int Dist_ArG;
int Dist_ArD;

void testTelemetres()
{
    Dist_AvG = telAvG.getDistance();
    Serial.print("Avant gauche : ");
    Serial.println(Dist_AvG);
    delay(1000);

    Dist_AvD = telAvD.getDistance();
    Serial.print("Avant droit : ");
    Serial.println(Dist_AvD);
    delay(1000);

    Dist_ArG = telArG.getDistance();
    Serial.print("Arriere gauche : ");
    Serial.println(Dist_ArG);
    delay(1000);

    Dist_ArD = telArD.getDistance();
    Serial.print("Arriere droit : ");
    Serial.println(Dist_ArD);
    delay(1000);

    Serial.println("");
}

/* // telemetre
int ArG; // 0 quand leds allumées == obstacle détecté
int ArD;
int pin_ArG = 4;
int pin_ArD = 5;
bool isObstacleArG = false;
bool isObstacleArD = false;
int cptObstacleArG = 0;

void obstacleArriereGauche(){
  //Serial.println("obstacle arriere gauche detecté");
  isObstacleArG++;
  if(cptObstacleArG > 1000){
    isObstacleArG = true;
  }
  //arret();
}

void obstacleArriereDroit(){
  //Serial.println("obstacle arriere droit detecté");
  isObstacleArD = true;
  //arret();
}

void NoObstacleArriereGauche(){
  isObstacleArG = 0;
  isObstacleArG = false;
}

void NoObstacleArriereDroit(){
  isObstacleArD = false;
}*/

/*#include <Arduino.h>
#include <Servo.h>
#include <SharpIR.h>
#include <MsTimer2.h>
#include <ServoPerso.h>
#include <Encoder.h>
#include "main.cpp"
#include "MotorsPerso.h"*/

#endif //TEST_ALLCOMPONANTS_TELEMETRESPERSO_H
