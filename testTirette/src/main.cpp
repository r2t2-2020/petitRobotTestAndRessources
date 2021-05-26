#include "Arduino.h"
#include <MsTimer2.h>
#include <Encoder.h>

const int pin_tirette = 4;
bool isTimerSet = false;


void flash()
{
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("TT");
    while(1);
}


void setup() {
    Serial.begin(9600);
    Serial.println("Test d'activation avec la tirette");

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(pin_tirette, INPUT_PULLUP);

    MsTimer2::set(5000, flash); // 500ms period
}


void loop() {
    while(digitalRead(pin_tirette) && !isTimerSet);
    if(!isTimerSet){
        MsTimer2::start();
        isTimerSet = true;
    }
    Serial.println("Running OK");
    //Serial.println("Running");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
    delay(500);

}


