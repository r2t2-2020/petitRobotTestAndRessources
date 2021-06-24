#include <Arduino.h>
#include <ServoPerso.h>
#include "AsservissementMoteurNlPerso.h"
#include <StrategiePerso.h>
#include <MsTimer2.h>
#include <TelemetresPerso.h>
#include <WallDetector.h>

// Tirette
const int pin_tirette = 4;
bool isTimerSet = false;

// crémaillère
int arret = 1520; //1510;
int vitesse = 200;
int duree = 700;


void finRun() {
    motorStopped_D = motorStopped_G = true;
    motorBreak_G();
    motorBreak_D();
    while(1);
}

void setup() {
    pinMode(wallDetector_L, INPUT_PULLUP);  // wall detector
    pinMode(wallDetector_R, INPUT_PULLUP);
    
    pinMode(50, INPUT);
    pinMode(51, INPUT);
    pinMode(52, INPUT);
    pinMode(53, INPUT);

    PCICR = 1;
    PCMSK0 = 0b00001111;

    sei();

    Serial.begin(9600);         // Initialisation port COM
    pinMode(pinPowerG, OUTPUT);    // Sorties commande moteur
    pinMode(motG_IN1, OUTPUT);
    pinMode(motG_IN2, OUTPUT);

    pinMode(pin_tirette, INPUT_PULLUP);
    //MsTimer2::set(100000, finRun); // MsTimer2 peut avoir des conflits avec d'autres librairies et certains pins (comme le 10)

    Myservo.attach(pin_servo);
    //Myservo.write(angle_depart);
    Myservo.write(arret);

    analogWrite(pinPowerG, 0);  // Initialisation sortie moteur Ã  0
    delay(300);                // Pause de 0,3 sec pour laisser le temps au moteur de s'arrÃ©ter si celui-ci est en marche
}

/* Fonction principale */
void loop() {


    //while(digitalRead(pin_tirette) && !isTimerSet);

    if(!isTimerSet){
        //MsTimer2::start();
        isTimerSet = true;
    }

   // strategieGauche();

    //move(1000, "forward");
    /*
    while(1){
        move(200, "forward");
        delay(400);
        move(200, "backward");
        delay(400);
    }
     */
    testWallDetector();

    disableTels();
    move(5000000, "rightForwardWall");
    while(1) {
        Serial.println("fini");
    }

    //*// TRATEGIE PRINCIPALE 2
     //sendArmToHome();
     int waitTime = 500;

     disableTels();

     move(330, "leftForward");
     delay(waitTime);

     move(500, "forward");
     delay(waitTime);

     move(300, "backward");
     delay(waitTime);

     move(360, "turnAroundLeft");
     delay(waitTime);
     ableTels();

     move(1420, "forward");
     delay(waitTime);



     move(90, "turnAroundRight");
     delay(waitTime);

     move(200, "forward");
     delay(waitTime);

     move(260, "backward");
     delay(waitTime);

     //deployArm();
     Myservo.write(arret+vitesse);
     delay(duree);
     Myservo.write(arret);
     delay(waitTime);

     move(650, "forward");
     delay(waitTime);


     //sendArmToHome();
     Myservo.write(arret-vitesse);
     delay(duree);
     Myservo.write(arret);
     delay(waitTime);
     // girouettes redréssées !!
     //*/ // après girouettes

 /*// TRATEGIE PRINCIPALE 1
    //sendArmToHome();
    int waitTime = 500;

    move(100, "forward");
    delay(waitTime);

    move(100, "turnAroundRight");
    delay(waitTime);

    disableTels();
    move(520, "forward");
    delay(waitTime);

    move(300, "backward");
    delay(waitTime);

    move(310, "turnAroundRight");
    delay(waitTime);
    ableTels();

    move(1420, "forward");
    delay(waitTime);



    move(90, "turnAroundRight");
    delay(waitTime);

    move(200, "forward");
    delay(waitTime);

    move(260, "backward");
    delay(waitTime);

    //deployArm();
    Myservo.write(arret+vitesse);
    delay(duree);
    Myservo.write(arret);
    delay(waitTime);

    move(650, "forward");
    delay(waitTime);


    //sendArmToHome();
    Myservo.write(arret-vitesse);
    delay(duree);
    Myservo.write(arret);
    delay(waitTime);
    // girouettes redréssées !!
    //*/ // après girouettes

    /*move(50, "backward");
    delay(waitTime);

    move(30, "rightBackward");
    delay(waitTime);

    deployArm();
    move(30, "forward");  // leftForward
    delay(waitTime);
    sendArmToHome();
    move(350, "rightBackward");
    delay(waitTime);

    move(500, "forward");
    delay(waitTime);

    move(110, "turnAroundLeft");
    delay(waitTime);

    move(500, "forward");
    delay(waitTime);

    move(110, "turnAroundRight");
    delay(waitTime);
    */



    /*// strategie Sud
    sendArmToHome();
    int waitTime = 500;
    move(100, "forward");
    delay(waitTime);

    move(100, "turnAroundRight");
    delay(waitTime);

    move(520, "forward");
    delay(waitTime);

    move(300, "backward");
    delay(waitTime);

    move(340, "turnAroundRight");
    delay(waitTime);

    move(1250, "forward");
    delay(waitTime);

    move(80, "turnAroundRight");
    delay(waitTime);

    move(1000, "forward");
    delay(waitTime);

    move(1100, "backward");
    delay(waitTime);

    deployArm();
    delay(waitTime);

    move(1000, "forward");
    delay(waitTime);
    //*/


    /* // test manche à air à reculons
    deployArm();
    move(30, "backward");
    delay(500);

    deployArm();
    delay(1000);

    sendArmToHome();
    delay(1000);

    move(200, "backward");
    delay(500);

    deployArm();
    delay(1000);

    sendArmToHome();
    delay(500);

    move(500, "backard");*/

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
    //delay(2000);

    //move(1000, "backward");
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