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
// http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega640-1280-1281-2560-2561-Datasheet-DS40002211A.pdf pour arduino mega

void setup() {
    Serial.begin(9600);

    //interruptions
    pinMode(50, INPUT_PULLUP);
    pinMode(51, INPUT_PULLUP);
    pinMode(52, INPUT_PULLUP);
    pinMode(53, INPUT_PULLUP);
    PCICR = 1;
    PCMSK0 = 0b00001111; // active les 4 premiers du groupe 0 donc les pins 50 à 53
    sei();
    //attachInterrupt(digitalPinToInterrupt(51), testServo, CHANGE);

    //tirette
    pinMode(pin_tirette, INPUT_PULLUP);
    MsTimer2::set(50000, finRun); // MsTimer2 peut avoir des conflits avec d'autres librairies et certains pins (comme le 10)
    //temps au bout du quel le robot s'arrete

    //servo moteur
    Myservo.attach(pin_servo);
    pinMode(5, INPUT_PULLUP);
    for(int i =8;i<14;i++)
    {
        pinMode(i,OUTPUT); // PINs en sortie
    }

    //moteurs
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


}

