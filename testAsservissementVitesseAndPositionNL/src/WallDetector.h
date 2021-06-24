//
// Created by gozlanp on 23/06/2021.
//

#ifndef TESTASSERVISSEMENTVITESSEANDPOSITIONNL_WALLDETECTOR_H
#define TESTASSERVISSEMENTVITESSEANDPOSITIONNL_WALLDETECTOR_H

#include <digitalWriteFast.h>

const int wallDetector_L = 18;
const int wallDetector_R = 19;

volatile bool isWall_L = false;
volatile bool isWall_R = false;

bool isWallDetectorEnabled = false;

const unsigned long dureeAntiRebond = 20;
unsigned long dateDernierChangementL = 0;
unsigned long dateDernierChangementR = 0;

int cpt_0_Left = 0;
int cpt_1_Left = 0;

void wallDetection_L(){
    unsigned long date = millis();
    if ((date - dateDernierChangementL) > dureeAntiRebond) {
        if (!isWall_L) {
            isWall_L = true;
            //cpt_0_Left++;
        } else {
            isWall_L = false;
            //cpt_1_Left++;
        }
        dateDernierChangementL = date;
    }
}

void wallDetection_R(){
    unsigned long date = millis();
    if ((date - dateDernierChangementR) > dureeAntiRebond) {
        if (!isWall_R) {
            isWall_R = true;
        } else {
            isWall_R = false;
        }
        dateDernierChangementR = date;
    }
}

void enableWallDetector(){
    attachInterrupt(digitalPinToInterrupt(wallDetector_L), wallDetection_L, CHANGE);
    attachInterrupt(digitalPinToInterrupt(wallDetector_R), wallDetection_R, CHANGE);
    delay(1000);
    isWall_L = isWall_R = false;
    cpt_0_Left = cpt_1_Left = 0;
    isWallDetectorEnabled = true;
}

void disableWallDetector(){
    detachInterrupt(digitalPinToInterrupt(wallDetector_L));
    detachInterrupt(digitalPinToInterrupt(wallDetector_R));
    isWallDetectorEnabled = false;
}

void testWallDetector(){
    enableWallDetector();
    while(1) {
        if (isWallDetectorEnabled) {
            Serial.print("WallLeft : ");
            Serial.print(isWall_L ? "true" : "false");
            Serial.print(" WallRight : ");
            Serial.println(isWall_R ? "true" : "false");
            delay(100);
        }
    }
}

void testWallDetectorCpt(){
    enableWallDetector();
    while(1) {
        if (isWallDetectorEnabled) {
            Serial.print("Cpt_0_Left : ");
            Serial.print(cpt_0_Left);
            Serial.print(" Cpt_1_Left : ");
            Serial.print(cpt_1_Left);
            Serial.print(" left State : ");
            Serial.println(digitalRead(wallDetector_L));
            delay(100);
        }
    }
}

#endif //TESTASSERVISSEMENTVITESSEANDPOSITIONNL_WALLDETECTOR_H
