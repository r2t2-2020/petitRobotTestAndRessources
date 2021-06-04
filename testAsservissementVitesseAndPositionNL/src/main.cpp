#include <Arduino.h>
#include <ServoPerso.h>
#include "AsservissementMoteurNlPerso.h"
#include <MsTimer2.h>

// Tirette
const int pin_tirette = 4;
bool isTimerSet = false;

void finRun() {
    motorStopped_D = motorStopped_G = true;
    motorBreak_G();
    motorBreak_D();
    while(1);

}

void setup() {
    Serial.begin(9600);         // Initialisation port COM
    pinMode(pinPowerG, OUTPUT);    // Sorties commande moteur
    pinMode( motG_IN1, OUTPUT );
    pinMode( motG_IN2, OUTPUT );

    pinMode(pin_tirette, INPUT_PULLUP);
    MsTimer2::set(10000, finRun); // MsTimer2 peut avoir des conflits avec d'autres librairies et certains pins (comme le 10)

    Myservo.attach(pin_servo);

    analogWrite(pinPowerG, 0);  // Initialisation sortie moteur Ã  0
    delay(300);                // Pause de 0,3 sec pour laisser le temps au moteur de s'arrÃ©ter si celui-ci est en marche
}

/* Fonction principale */
void loop() {


    while(digitalRead(pin_tirette) && !isTimerSet);

    if(!isTimerSet){
        MsTimer2::start();
        isTimerSet = true;
    }
    // testServo();
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
    delay(2000);
    move(1000, "forward");
    /*
    for(int i=0; i<5; i++) {
        move(1000, "forward");
        delay(1000);
        move(1000, "backward");
        delay(1000);
    }
    //*/
    //move(300, "leftForward");
    /*
    move(250, "forward");
    move(125, "turnAroundLeft"); //350
    move(1000, "forward");
    delay(1000);
    move(1000, "backward");
     */
    //move(1000, "backward");
    Serial.println("Terminé");
    while(1);
}