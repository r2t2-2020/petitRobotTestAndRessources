//
// Created by gozlanp on 26/05/2021.
//

#ifndef TEST_ALLCOMPONANTS_SERVOPERSO_H
#define TEST_ALLCOMPONANTS_SERVOPERSO_H

#include <Servo.h>
//#include <ServoTimer2.h>

//servo positionné sur la gauche du robot
//Servo Myservo;
//Servo Mypavillon;
Servo Myservo;

int pin_servo = 6; //6
int position = 80; // position souhaitée
int angle_depart = 150; // vers l'avant
int angle_final = 10; //vers l'arriere
int increment = 10; // nombre de pas à la fois

int pin_Pavillon = 48;

// crémaillère
int arret = 1520; //1510; //1515 avec servotimer2
int vitesse = 200;
int duree = 640;

void testServo(){
    Myservo.write(arret+vitesse);
    delay(duree);
    Myservo.write(arret);
    delay(1000);
    Myservo.write(arret-vitesse);
    delay(duree);
    Myservo.write(arret);
    delay(1000);
}

void openCremaillereEst(){
    Myservo.attach(pin_servo);
    Myservo.write(arret+vitesse);
    delay(duree+100);
    Myservo.write(arret);
    delay(duree);
    Myservo.detach();
}

void closeOuestCremaillere(){
    openCremaillereEst();
}

void closeCremaillereEst(){
    Myservo.attach(pin_servo);
    Myservo.write(arret-vitesse);
    delay(duree);
    Myservo.write(arret);
    Myservo.detach();
}

void openCremaillerOuest(){
    closeCremaillereEst();
}

// pour le pavillon
void positionDepartPavillon(){
    Myservo.attach(pin_Pavillon);

    delay(500);
    Myservo.write(90);
    delay(500);

    Myservo.detach();
}

void deployerPavillon(){
    Myservo.attach(pin_Pavillon);

    delay(500);
    Myservo.write(0);
    delay(500);

    Myservo.detach();
}

void deployerPavillonFin(){
    for(int i=90; i<=5; i-=5){
        Myservo.write(i);
    }
}

#endif //TEST_ALLCOMPONANTS_SERVOPERSO_H

