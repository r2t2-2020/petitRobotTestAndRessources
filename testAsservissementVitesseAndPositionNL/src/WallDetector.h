//
// Created by gozlanp on 23/06/2021.
//

#ifndef TESTASSERVISSEMENTVITESSEANDPOSITIONNL_WALLDETECTOR_H
#define TESTASSERVISSEMENTVITESSEANDPOSITIONNL_WALLDETECTOR_H

const int wallDetector_L = 18;
const int wallDetector_R = 19;

volatile bool isWall_L = false;
volatile bool isWall_R = false;

bool isWallDetectorEnabled = false;

void wallDetection_L(){
    isWall_L = (digitalRead(wallDetector_L) == HIGH) ? true : false;
    //if (isWall_L) Serial.println("wall Left");
}

void wallDetection_R(){
    isWall_R = (digitalRead(wallDetector_R) == HIGH) ? true : false;
    //if (isWall_L) Serial.println("wall Right");
}

void enableWallDetector(){
    attachInterrupt(digitalPinToInterrupt(wallDetector_L), wallDetection_L, CHANGE);
    attachInterrupt(digitalPinToInterrupt(wallDetector_R), wallDetection_R, CHANGE);
    isWall_L = isWall_R = false;
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
            Serial.print(isWall_L);
            Serial.print(" WallRight : ");
            Serial.println(isWall_R);
            delay(200);
        }
    }
}

#endif //TESTASSERVISSEMENTVITESSEANDPOSITIONNL_WALLDETECTOR_H
