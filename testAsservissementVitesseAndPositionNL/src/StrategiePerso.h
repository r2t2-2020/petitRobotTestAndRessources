//
// Created by gozlanp on 10/06/2021.
//


#ifndef TESTASSERVISSEMENTVITESSEANDPOSITIONNL_STRATEGIEPERSO_H
#define TESTASSERVISSEMENTVITESSEANDPOSITIONNL_STRATEGIEPERSO_H

#include <ServoPerso.h>
#include "AsservissementMoteurNlPerso.h"

bool justePhare = false;

int waitTime = 500;

// Carte Pico
const int pin_endingZoneTaken = 39; // la pico a pris la photo et on peut lire le pin whichEndingZone
const int pin_whichEndingZone = 43; // zone dans laquel on doit finir le run
const int pin_readyToTakeThePicture = 41; // pin en sortie que la pico va regarder pour savoir quand prendre la photo
const int NORD = 1;
const int SUD = 0;
int whichEndingZone = 0;

void strategieEst(){
    bool justWallManches = false;
    disableTels();

    if(!justWallManches) {

        /*move(100000, "backwardWall");
        delay(waitTime);*/

        //ableTels();
        move(330, "leftForward");
        delay(waitTime);

        // approche phare
        move(100, "forward");
        delay(waitTime);
        move(50, "rightForward");
        delay(waitTime);
        move(30, "leftForward");
        delay(waitTime);

        disableTels(); // phare
        move(2000, "forwardWall");  // 500
        delay(waitTime);
    }

    if(!justePhare) {
        if(!justWallManches) {
            move(300, "backward");
            delay(waitTime);

            move(300, "turnAroundRight");  //320
            delay(waitTime);

            move(160, "forward");
            delay(waitTime);

            move(12, "turnAroundLeft"); //15
            delay(waitTime);

            // Manoeuvre approche des manches à air
        }
        move(2000, "forwardWall");
        delay(waitTime);

        //move(20, "forward");
        //delay(waitTime);

        /*

        move(30, "rightBackward");
        delay(waitTime);

        move(120, "leftForward");
        delay(waitTime);

        move(220, "forward");
        delay(waitTime);

        move(15, "leftBackward");
        delay(waitTime);

        move(100000, "backwardWall");
        delay(waitTime);

         */

        /*
        move(12, "leftBackward"); //50
        delay(waitTime);

        move(12, "rightBackward");
        delay(waitTime);

        for (int i = 0; i < 4; i++) {
            move(19, "leftForward");
            delay(waitTime);
            move(19, "rightBackward");
            delay(waitTime);
        }
        move(30, "backward");
        delay(waitTime);
         */

        move(50, "backward");
        delay(waitTime);
        move(300, "leftForward");
        delay(waitTime);
        move(10000, "backwardWall");
        delay(waitTime);


        move(10, "forward");
        delay(waitTime);

        openCremaillereEst();

        delay(1000);

        move(630, "forward");  //640
        delay(waitTime);

        // on rentre la cremaillere
        closeCremaillereEst();

        move(100, "backward");

        move(330, "leftForward");
        delay(waitTime);

        move(50, "forward");
        delay(waitTime);

        ableTels();
        move(500, "forward");
        delay(waitTime);
    }
}

void strategieOuest(){

    disableTels();


    //// DEBUT TEST QUE COIN
    /*
    move(50, "backward");
    delay(waitTime);

    move(30, "leftBackward");
    delay(waitTime);

    move(80, "rightForward");
    delay(waitTime);

    move(250, "forward");
    delay(waitTime);

    move(2000, "forwardWall");
    delay(waitTime);
     */

    //// FIN TEST QUE COIN

    /*move(100000, "backwardWall");
    delay(waitTime);*/

    //ableTels();
    move(330, "rightForward");
    delay(waitTime);

    // approche phare
    move(100, "forward");
    delay(waitTime);
    // ICIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII
    move(50, "leftForward");
    delay(waitTime);
    move(30, "rightForward");
    delay(waitTime);

    disableTels(); // phare
    move(20000, "forwardWall");  // 500
    delay(waitTime);

    if(!justePhare){
        move(300, "backward"); // on part du phare
        delay(waitTime);

        //ableTels();  // fin phare
        move(335, "turnAroundRight");//350
        delay(waitTime);

        move(1200, "forward");

        //on va taper le mur des manches a air
        disableTels();
        move(2000, "forwardWall");
        delay(waitTime);
        move(15, "backward");
        //delay(waitTime);

        /*
        move(40, "rightBackward");
        delay(waitTime);

        move(100, "backward");
        delay(waitTime);

        move(30, "leftBackward");
        delay(waitTime);

        move(160, "forward");
        delay(waitTime);

        move(60, "turnAroundLeft");
        delay(waitTime);
         */

        for (int i = 0; i < 4; i++) {
            move(21, "leftBackward");
            delay(waitTime);
            move(21, "rightForward");
            delay(waitTime);
        }
        move(30, "backward");
        delay(waitTime);

        /*
        move(50, "backward");
        delay(waitTime);

        move(30, "leftBackward");
        delay(waitTime);

        move(100, "rightForward");
        delay(waitTime);

        move(10, "leftBackward");
        delay(waitTime);

        move(250, "forward");
        delay(waitTime);
         */

        /*
        move(100000, "backwardWall");
        delay(waitTime);
         */

        move(10, "forward");
        delay(waitTime);


        openCremaillerOuest();

        delay(1000);

        move(10, "rightForward"); // 20
        delay(waitTime);


        move(300, "forward");//650
        delay(waitTime);

        move(10, "leftForward");
        delay(waitTime);

        move(310, "forward");//650  //320
        delay(waitTime);

        // on rentre la cremaillere
        closeOuestCremaillere();

        move(100, "backward");

        move(330, "rightForward");
        delay(waitTime);

        move(50, "forward");
        delay(waitTime);

        ableTels();
        move(500, "forward");
        delay(waitTime);
        //ICIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII FINNNNNNNNNNNNNN
    }
}

void finNordPourOuest(){
    move(80, "rightForward"); //100
    delay(waitTime);

    move(200, "forward");
    delay(waitTime);

    move(100, "rightForward");
    delay(waitTime);

    move(2000, "forwardWall");
    delay(waitTime);

    move(10, "backward");
    delay(waitTime);

    move(280, "rightBackward");
    delay(waitTime);

    /*move(20, "forwardLeft");
    delay(waitTime);*/

    // on arrive dans l'angle nord où se trouve le phare
    disableTels();
    move(2000, "forwardWall");
    delay(waitTime);
}

void finSudPourOuest(){
    move(100, "leftBackward");
    delay(waitTime);

    move(200, "forward");
    delay(waitTime);

    move(50, "rightForward");
    delay(waitTime);

    move(2000, "forwardWall");
    delay(waitTime);
}

void finNordPourEst(){

    move(80, "leftForward"); //100
    delay(waitTime);

    move(200, "forward");
    delay(waitTime);

    move(100, "leftForward");
    delay(waitTime);

    move(2000, "forwardWall");
    delay(waitTime);

    move(20, "backward");
    delay(waitTime);

    move(280, "leftBackward");
    delay(waitTime);

    move(20, "forwardLeft");
    delay(waitTime);

    disableTels();
    move(2000, "forwardWall");
    delay(waitTime);
}

void finSudPourEst(){

    move(100, "rightBackward");
    delay(waitTime);

    move(200, "forward");
    delay(waitTime);

    move(50, "leftForward");
    delay(waitTime);

    move(2000, "forwardWall");
    delay(waitTime);
}

void strategieGirouette(){
    //digitalWrite(pin_readyToTakeThePicture, HIGH);

    //while(1) Serial.println(digitalRead(pin_endingZoneTaken));

    /*int i = 0;
    while(digitalRead(pin_endingZoneTaken) == LOW){
        Serial.print("waiting ");
        Serial.println(i++);
    }*/

    //on peut lire dans quelle zone finir
    //whichEndingZone = digitalRead(pin_whichEndingZone);

    whichEndingZone = 1;

    const int pin_camp = 30;
    pinMode(pin_camp, INPUT);

    int camp = digitalRead(pin_camp);

    if(whichEndingZone == NORD){
        if(camp == 1){ //ouest
            if(!justePhare)finNordPourOuest();
        }else{
            if(!justePhare)finNordPourEst();
        }
    }

    if(whichEndingZone == SUD){
        if(camp == 1){ //ouest
            if(!justePhare)finSudPourOuest();
        }
        else{
            if(!justePhare)finSudPourEst();
        }
    }
}



#endif //TESTASSERVISSEMENTVITESSEANDPOSITIONNL_STRATEGIEPERSO_H
