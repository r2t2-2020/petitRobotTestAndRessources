#include <Arduino.h>
#include <ServoPerso.h>
#include "AsservissementMoteurNlPerso.h"


void setup() {
    Serial.begin(9600);         // Initialisation port COM
    pinMode(pinPowerG, OUTPUT);    // Sorties commande moteur
    pinMode( motG_IN1, OUTPUT );
    pinMode( motG_IN2, OUTPUT );

    Myservo.attach(pin_servo);

    analogWrite(pinPowerG, 0);  // Initialisation sortie moteur Ã  0
    delay(300);                // Pause de 0,3 sec pour laisser le temps au moteur de s'arrÃ©ter si celui-ci est en marche
}

/* Fonction principale */
void loop() {
    testServo();
    //move(5*960);//4*960);
    //Serial.println(distanceToNbTicks(2*3.14159265358*55));
    //move(1000, "both");
    /*
    move(355, "rightForward");
    delay(500);
    move(355, "forward");
    delay(500);
    move(355, "backward");
    //*/
    move(1000, "forward");
    Serial.println("Terminé");
    while(1);
}