#include <Arduino.h>
#include <ServoPerso.h>
#include "AsservissementMoteurNlPerso.h"
#include <StrategiePerso.h>
#include <MsTimer2.h>
#include <TelemetresPerso.h>
#include <WallDetector.h>
#include <TimerFour.h>

//
//https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.youtube.com%2Fwatch%3Fv%3DBmM5qd0puJs&psig=AOvVaw3NKh5V9UZsx39Suz8dqiji&ust=1624702086108000&source=images&cd=vfe&ved=0CAcQjRxqFwoTCOCFu4nFsvECFQAAAAAdAAAAABAl
//timer5 lib: https://forum.arduino.cc/t/timer-4-and-timer-5-libraries-for-arduino-mega/214949

// Tirette
const int pin_tirette = 3;
bool isTimerSet = false;

const int pin_camp = 30;

bool pavillonFin = false;

void finRun() {
    Myservo.attach(pin_Pavillon);

    deployerPavillonFin();
    Myservo.detach();

    motorStopped_D = motorStopped_G = true;
    motorBreak_G();
    motorBreak_D();

    while(1);
}

//int debutRun = 0;
void timerPavillon(){
    /*  // déplacé dans le main
    if(millis() - debutRun >= 95000){
        pavillonFin = true;
    }
     */
    unsigned long currentMillis = millis();
    if(currentMillis - debutRun >= 98000){
        motorStopped_D = motorStopped_G = true;
        motorBreak_G();
        motorBreak_D();

        //while(1);
        motorStoppedForever = true;
    }

}

void setup() {
    pinMode(pin_camp, INPUT);

    // pour girouette
    pinMode(pin_endingZoneTaken, INPUT);
    pinMode(pin_whichEndingZone, INPUT);
    pinMode(pin_readyToTakeThePicture, OUTPUT);

    digitalWrite(pin_readyToTakeThePicture, 0);

    pinMode(wallDetector_L, INPUT_PULLUP);  // wall detector
    pinMode(wallDetector_R, INPUT_PULLUP);

    pinMode(50, INPUT);
    pinMode(51, INPUT);
    pinMode(52, INPUT);
    pinMode(53, INPUT);

    sei();

    Serial.begin(9600);         // Initialisation port COM
    pinMode(pinPowerG, OUTPUT);    // Sorties commande moteur
    pinMode(motG_IN1, OUTPUT);
    pinMode(motG_IN2, OUTPUT);

    pinMode(pin_tirette, INPUT_PULLUP);

    MsTimer2::set(2000, timerPavillon);

    analogWrite(pinPowerG, 0);  // Initialisation sortie moteur Ã  0
    delay(300);                // Pause de 0,3 sec pour laisser le temps au moteur de s'arrÃ©ter si celui-ci est en marche

    //pavillon
    positionDepartPavillon();
}

bool coteGauche = false;
int camp = 2;

/* Fonction principale */
void loop() {

    while(digitalRead(pin_tirette) && !isTimerSet);
    camp = digitalRead(pin_camp);

    if(!isTimerSet){
        debutRun = millis();
        MsTimer2::start();
        isTimerSet = true;
    }


    /*// test picture
    delay(4000);
    digitalWrite(pin_readyToTakeThePicture, HIGH);
    while(1);*/

    // fin testvpicture

    if(camp == 1){
       strategieOuest();
       Serial.println("CAMP OUEST");
    }

    if(camp == 0){
       strategieEst();
       Serial.println("CAMP EST");
    }

    Serial.println("Ready to take picture");
    strategieGirouette();

    while(!pavillonFin) {
        if (millis() - debutRun >= 96000) {
            pavillonFin = true;
        }
    }

    if(pavillonFin){
        deployerPavillon();
    }

    Serial.println("Terminé");
    while(1);
}