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
    /*
        if(digitalRead(53) == 0){ //(PINB & 1<<PORTB0) &&
            if(isObstacle_AR_D == false){
                Serial.println("je suis le pin 53, arriere droite");
                isObstacle_AR_D = isObstacle_AR_D ? false : true;
            }
        }

        if( digitalRead(52) == 0){
            if (isObstacle_AR_G == false){
                Serial.println("je suis le pin 52, arriere gauche");
                isObstacle_AR_G = isObstacle_AR_G ? false : true;
            }
        }
        if(digitalRead(51) == 0){
            if(isObstacle_AV_D == false){
                Serial.println("je suis le pin 51, avant droite");
                isObstacle_AV_D = isObstacle_AV_D ? false : true;
            }
        }
        */
        if(digitalRead(50) == 0){
            Serial.println("je suis le pin 50, avant gauche");
            if (isObstacle_AV) {
                isObstacle_AV = false;
                Serial.println("isObstacle_AV_G : false");
            } else {
                isObstacle_AV = true;
                Serial.println("isObstacle_AV_G : true");
            }
        }
}


#endif //TESTASSERVISSEMENTVITESSEANDPOSITIONNL_TELEMETRESPERSO_H
