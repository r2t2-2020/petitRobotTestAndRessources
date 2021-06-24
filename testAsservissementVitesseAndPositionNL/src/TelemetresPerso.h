//
// Created by gozlanp on 23/06/2021.
//

#ifndef TESTASSERVISSEMENTVITESSEANDPOSITIONNL_TELEMETRESPERSO_H
#define TESTASSERVISSEMENTVITESSEANDPOSITIONNL_TELEMETRESPERSO_H

bool isObstacle_AR = false;
bool isObstacle_AV = false;

void disableTels(){
    PCMSK0 = 0b00000000;
}

void ableTels(){
    PCMSK0 = 0b00001111;
}

bool detectObstacle_AV(){
    return digitalRead(50) == 0;
}


ISR(PCINT0_vect){
        if(digitalRead(53) == 0){
            //Serial.println("je suis le pin 53, arriere droite");
            isObstacle_AR = isObstacle_AR ? false : true;
            //Serial.println("isObstacle_AR : " + isObstacle_AR);
        }

        if(digitalRead(52) == 0){
            //Serial.println("je suis le pin 52, arriere gauche");
            isObstacle_AR = isObstacle_AR ? false : true;
            //Serial.println("isObstacle_AR : " + isObstacle_AR);
        }

        if(digitalRead(51) == 0){
            //Serial.println("je suis le pin 51, avant droite");
            isObstacle_AV = isObstacle_AV ? false : true;
            //Serial.println("isObstacle_AV : " + isObstacle_AV);
        }

        if(digitalRead(50) == 0){
            //Serial.println("je suis le pin 50, avant gauche");
            isObstacle_AV = isObstacle_AV ? false : true;
            //Serial.println("isObstacle_AV : " + isObstacle_AV);
        }
}


#endif //TESTASSERVISSEMENTVITESSEANDPOSITIONNL_TELEMETRESPERSO_H
