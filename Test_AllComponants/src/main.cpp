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

    //interruptions
    pinMode(13, INPUT_PULLUP); //_PULLUP
    pinMode(53, INPUT_PULLUP);
    PCICR =1;
    PCMSK0 = 0b10000001; // masque pour 0 et 7 eme bits, permet de les activer en interruption
    sei();

    //attachInterrupt(digitalPinToInterrupt(51), testServo, CHANGE);

    pinMode(pin_tirette, INPUT_PULLUP);
    MsTimer2::set(50000, finRun);

    Myservo.attach(pin_servo);
    pinMode(5, INPUT_PULLUP);
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

