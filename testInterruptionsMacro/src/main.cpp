#include <Arduino.h>

void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

// ISR Routine to handle each group

ISR (PCINT0_vect) // handle pin change interrupt for PB0 to PB7 (PIN 53 52 51 50 10 11 12 13)
        {
            if(digitalRead(51) == HIGH) {
                digitalWrite(LED_BUILTIN, HIGH);
            }
                // Do what you want here, it will be triggered whenever one of the eight pins change.
        }


void setup() {
    pciSetup(50);
    for (int i=50; i<=53; i++) {
        pinMode( i, INPUT);    // INPUT is already on by default but ...
        digitalWrite(i,HIGH);  // set pullups, if necessary ...
        pciSetup(i);           // enable interrupt for pin...
    }
    pinMode(LED_BUILTIN, OUTPUT);
// write your initialization code here
}

void loop() {
// write your code here
}