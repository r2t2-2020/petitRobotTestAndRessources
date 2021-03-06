//
// Created by gozlanp on 26/05/2021.
//

#ifndef TEST_ALLCOMPONANTS_SERVOPERSO_H
#define TEST_ALLCOMPONANTS_SERVOPERSO_H

//servo positionné sur la gauche du robot
Servo Myservo;

int pin_servo = 6;
int position = 80; // position souhaitée
int angle_depart = 140; // vers l'avant
int angle_final = 10; //vers l'arriere
int increment = 5; // nombre de pas à la fois

void testServo(){
    Myservo.write(position);

    for(int i=position; i<=angle_depart; i += increment){
        Myservo.write(i);
        delay(200);
    }
}


/*#include <Arduino.h>
#include <Servo.h>
#include <SharpIR.h>
#include <MsTimer2.h>
#include <Encoder.h>
#include "../.pio/libdeps/megaatmega2560/Servo/examples/Knob/Knob.ino"
#include "main.cpp"
#include "MotorsPerso.h"*/

#endif //TEST_ALLCOMPONANTS_SERVOPERSO_H
