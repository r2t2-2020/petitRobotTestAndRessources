#include <Arduino.h>
#include <Servo.h>
#include <SharpIR.h>
#include <MsTimer2.h>
#include <ServoPerso.h>
#include <Encoder.h>
#include "MotorsPerso.h"
#include "TelemetresPerso.h"
#include "EncoderPerso.h"
#include "TirettePerso.h"
#include "Strategies.h"

void setup() {
    Serial.begin(9600);

    pinMode(pin_tirette, INPUT_PULLUP);
    MsTimer2::set(50000, finRun);

    Myservo.attach(pin_servo);

    for(int i =8;i<14;i++)
    {
        pinMode(i,OUTPUT); // PINs en sortie
    }

    digitalWrite(IN1,0);
    digitalWrite(IN2,0);
    digitalWrite(IN3,0);
    digitalWrite(IN4,0);

    analogWrite(ENA,0); // faire des rampes
    analogWrite(ENB,0);

}

void loop() {

    while(digitalRead(pin_tirette) && !isTimerSet);
    if(!isTimerSet){
        MsTimer2::start();
        isTimerSet = true;
    }
    Serial.println("Running OK");
    //Serial.println("Running");
    delay(500);

    while(1){
        pente();
    }
}

