//
// Created by gozlanp on 26/05/2021.
//

#ifndef TEST_ALLCOMPONANTS_SERVOPERSO_H
#define TEST_ALLCOMPONANTS_SERVOPERSO_H

#include <Servo.h>

//servo positionné sur la gauche du robot
Servo Myservo;

int pin_servo = 6;
int position = 80; // position souhaitée
int angle_depart = 150; // vers l'avant
int angle_final = 10; //vers l'arriere
int increment = 10; // nombre de pas à la fois

void testServo(){
    Myservo.write(position);

    for(int i=position; i>=angle_final; i -= increment){
        Myservo.write(i);
        delay(200);
    }
    //*/
}

void deployArm(){
    Myservo.write(position);
}

void sendArmToHome(){
    Myservo.write(angle_depart);
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
