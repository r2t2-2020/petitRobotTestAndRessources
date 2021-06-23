//
// Created by gozlanp on 10/06/2021.
//


#ifndef TESTASSERVISSEMENTVITESSEANDPOSITIONNL_STRATEGIEPERSO_H
#define TESTASSERVISSEMENTVITESSEANDPOSITIONNL_STRATEGIEPERSO_H

#include <ServoPerso.h>
#include "AsservissementMoteurNlPerso.h"

void strategieDroite(){

    sendArmToHome();
    int waitTime = 500;

    move(100, "forward");
    delay(waitTime);
    //
    move(100, "turnAroundRight");
    delay(waitTime);

    move(520, "forward");
    delay(waitTime);
//
    move(300, "backward");
    delay(waitTime);

    move(320, "turnAroundRight");
    delay(waitTime);

    move(1420, "forward");
    delay(waitTime);

    deployArm();
    delay(waitTime);

    move(100, "turnAroundRight");
    delay(waitTime);

    move(600, "forward");
    delay(waitTime);

    sendArmToHome();
    delay(waitTime);
    // girouettes redréssées !!
    // après girouettes

    move(50, "backward");
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
}

void strategieGauche(){
    sendArmToHome();
    int waitTime = 500;

    move(100, "forward");
    delay(waitTime);

    move(100, "turnAroundLeft");
    delay(waitTime);

    move(520, "forward");
    delay(waitTime);

    move(300, "backward");
    delay(waitTime);

    move(320, "turnAroundLeft");
    delay(waitTime);

    move(1420, "forward");
    delay(waitTime);

    deployArm();
    delay(waitTime);

    move(100, "turnAroundLeft");
    delay(waitTime);

    move(600, "forward");
    delay(waitTime);

    sendArmToHome();
    delay(waitTime);


}


#endif //TESTASSERVISSEMENTVITESSEANDPOSITIONNL_STRATEGIEPERSO_H
