//
// Created by gozlanp on 03/06/2021.
//

#ifndef TESTASSERVISSEMENTVITESSEANDPOSITIONNL_ASSERVISSEMENTMOTEURNLPERSO_H
#define TESTASSERVISSEMENTVITESSEANDPOSITIONNL_ASSERVISSEMENTMOTEURNLPERSO_H

#include <SimpleTimer.h>
#include <TelemetresPerso.h>
#include <WallDetector.h>


SimpleTimer timer;                  // Timer pour Ã©chantillonnage
volatile int timerID; // Numéro du timer pour pouvoir l'arrêter

volatile unsigned int tick_codeuse_pos_G = 0; // unsigned int
volatile unsigned int tick_codeuse_pos_D = 0;
unsigned int tick_codeuse_G = 0;     // Compteur de tick de la codeuse du moteur Gauche
unsigned int tick_codeuse_D = 0;     // Compteur de tick de la codeuse du moteur Droit
int vitMoteur_G = 0;                 // Commande du moteur Gauche
int vitMoteur_D = 0;                 // Commande du moteur Droite

const int frequence_echantillonnage = 100; // FrÃ©quence d'exÃ©cution de l'asservissement
const int rapport_reducteur = 30;          // Rapport nombre de tours de l'arbre moteur et de la roue
const int tick_par_tour_codeuse = 32;  //64 tick sur deux capteurs hall, ici un seul capteur

//definition des entrÃ©es Moteur Gauche
const int motG_IN1 = 8;    // Commande de sens moteur, Input 1
const int motG_IN2 = 9;    // Commande de sens moteur, Input 2
const int pinPowerG  = 7;    // Commande de vitesse moteur, Output Enabled1
volatile bool motorStopped_G = true;  // indique si un moteur a été stoppé pour ne plus l'asservir

//definition des entrÃ©es Moteur Droite
const int motD_IN3 = 12;    // Commande de sens moteur, Input 1
const int motD_IN4 = 11;    // Commande de sens moteur, Input 2
const int pinPowerD  = 13;    // Commande de vitesse moteur, Output Enabled1
volatile bool motorStopped_D = true;

//consigne en tour/s
//const float consigne_moteur_G = 0;//2;  // Consigne nombre de tours de roue par seconde moteur Gauche
float consigne_moteur_G = 0;//const float consigne_moteur_D = 0;//2;  // Consigne nombre de tours de roue par seconde moteur Droit
float consigne_moteur_D = 0;
void (*directionFunction_L)(int);
void (*directionFunction_D)(int);

volatile unsigned int consigneNbTick_G = 0;
volatile unsigned int consigneNbTick_D = 0;

// init calculs asservissement PID
float erreur_G_precedente = consigne_moteur_G; // (en tour/s)
float somme_erreur_G = 0;
float erreur_D_precedente = consigne_moteur_D; // (en tour/s)
float somme_erreur_D = 0;

//Definition des constantes du correcteur PID
const float kpG = 300;// 200; //350; //1100; // Coefficient proportionnel (choisis par essais successifs)
const float kiG = 0.6;//0.2; //5;   // Coefficient intÃ©grateur
const float kdG = 0;//200;//50; //100; // Coefficient dÃ©rivateur

const float kpD = 300;//270;//350; //1000; // Coefficient proportionnel (choisis par essais successifs)
const float kiD = 0.9;
const float kdD = 0;//200;

void nothing(int) {}

void motorForward_G(int powerRate ) {
    digitalWrite(motG_IN1, HIGH);
    digitalWrite(motG_IN2, LOW);
    analogWrite(pinPowerG, powerRate);
}

void motorForward_D(int powerRate ) {
    digitalWrite(motD_IN3, HIGH);
    digitalWrite(motD_IN4, LOW);
    analogWrite(pinPowerD, powerRate);
}

void motorBackWard_G(int powerRate ) {
    digitalWrite(motG_IN1, LOW);
    digitalWrite(motG_IN2, HIGH);
    analogWrite(pinPowerG, powerRate);
}

void motorBackWard_D(int powerRate ) {
    digitalWrite(motD_IN3, LOW);
    digitalWrite(motD_IN4, HIGH);
    analogWrite(pinPowerD, powerRate);
}

void motorBreak_D() {
    digitalWrite(motD_IN3, HIGH);
    digitalWrite(motD_IN4, HIGH);
    analogWrite(pinPowerD, 0);
}

void motorBreak_G() {
    digitalWrite(motG_IN1, HIGH);
    digitalWrite(motG_IN2, HIGH);
    analogWrite(pinPowerG, 0);
}

//---- Interruption sur tick de la codeuse du moteur Gauche
void compteur_G() {
    tick_codeuse_G++;
    tick_codeuse_pos_G++;
    //*
    if(tick_codeuse_pos_G >= consigneNbTick_G) {
        motorBreak_G();
        motorStopped_G = true;
        if(motorStopped_D) timer.disable(timerID);
        detachInterrupt(digitalPinToInterrupt(21));
        tick_codeuse_pos_G = 0;
    }
    //*/
    // On incrÃ©mente le nombre de tick de la codeuse.   un seul sens
}

//---- Interruption sur tick de la codeuse du moteur Droit
void compteur_D() {
    tick_codeuse_D++;
    tick_codeuse_pos_D++;
    //*
    if(tick_codeuse_pos_D >= consigneNbTick_D) {
        motorBreak_D();
        motorStopped_D = true;
        if(motorStopped_G) timer.disable(timerID);
        detachInterrupt(digitalPinToInterrupt(20));
        tick_codeuse_D = 0;
    }
    //*/
    // On incrÃ©mente le nombre de tick de la codeuse.   un seul sens
}


//---- Interruption pour calcul du P
void asservissement(){

    // Calcul de l'erreur_G
    int frequence_codeuse_G = frequence_echantillonnage * tick_codeuse_G; //100*tick_codeuse_G
    int frequence_codeuse_D = frequence_echantillonnage * tick_codeuse_D; //100*tick_codeuse_G

    float vit_roue_tour_sec_G = (float)frequence_codeuse_G / (float)tick_par_tour_codeuse / (float)rapport_reducteur;    //(100*tick_codeuse_G)/32/19
    float vit_roue_tour_sec_D = (float)frequence_codeuse_D / (float)tick_par_tour_codeuse / (float)rapport_reducteur;    //(100*tick_codeuse_G)/32/19
    float erreur_G = (consigne_moteur_G) - vit_roue_tour_sec_G; // pour le proportionnel
    float erreur_D = (consigne_moteur_D) - vit_roue_tour_sec_D; // pour le proportionnel

    somme_erreur_G += erreur_G; // pour l'intÃ©grateur
    somme_erreur_D += erreur_D; // pour l'intÃ©grateur

    float delta_erreur_G = erreur_G - erreur_G_precedente;  // pour le dÃ©rivateur
    erreur_G_precedente = erreur_G;
    float delta_erreur_D = erreur_D - erreur_D_precedente;  // pour le dÃ©rivateur
    erreur_D_precedente = erreur_D;


    // RÃ©initialisation du nombre de tick des  codeuses
    tick_codeuse_G = 0;
    tick_codeuse_D = 0;

    // P : calcul de la commande
    vitMoteur_G = kpG*erreur_G + kiG*somme_erreur_G + kdG*delta_erreur_G;  //somme des trois erreur_Gs
    vitMoteur_D = kpD*erreur_D + kiD*somme_erreur_D + kdD*delta_erreur_D;  //somme des trois erreur_Gs

    // Normalisation et contrÃ´le du moteur de Gauche
    if ( !motorStopped_G ) {
        if (vitMoteur_G > 255) {
            vitMoteur_G = 255;  // sachant que l'on est branchÃ© sur un pont en H L293D
        } else if (vitMoteur_G < 0) {
            vitMoteur_G = 0;
        }
    }

    // Normalisation et contrÃ´le du moteur de Droite
    if ( !motorStopped_D ) {
        if (vitMoteur_D > 255) {
            vitMoteur_D = 255;  // sachant que l'on est branchÃ© sur un pont en H L293D
        } else if (vitMoteur_D < 0) {
            vitMoteur_D = 0;
        }
    }

    /*
    Serial.print(!motorStopped_G);
    Serial.print(" : ");
    Serial.print(!motorStopped_D);
    Serial.println();
     */
    if (!motorStopped_G ) directionFunction_L(vitMoteur_G);
    if (!motorStopped_D ) directionFunction_D(vitMoteur_D);
    /*// Affiche nbTick
    Serial.print(tick_codeuse_pos_G);
    Serial.print(" : ");
    Serial.print(tick_codeuse_pos_D);
    Serial.println();
    //*/

    /*// Affiche vitesse
    Serial.print(vit_roue_tour_sec_G);  // affiche Ã  gauche la vitesse et Ã  droite l'erreur_G
    Serial.print(" : ");
    Serial.print(vit_roue_tour_sec_D);  // affiche Ã  gauche la vitesse et Ã  droite l'erreur_D
    Serial.println();
    //*/

    /*// Affiche erreur
    Serial.print(erreur_G, 4);
    Serial.print(" : ");
    Serial.print(vitMoteur_G);
    Serial.println();
    //*/
}

int distanceToNbTicks(float distance){
    float pi = 3.1415926535879323;
    float r = 55;
    float perim = 2*pi*r;
    return (int) distance/(perim/960);
}

void move(float distance, String direction){

    tick_codeuse_pos_G = 0; // unsigned int
    tick_codeuse_pos_D = 0;
    tick_codeuse_G = 0;     // Compteur de tick de la codeuse du moteur Gauche
    tick_codeuse_D = 0;     // Compteur de tick de la codeuse du moteur Droit
    vitMoteur_G = 0;                 // Commande du moteur Gauche
    vitMoteur_D = 0;                 // Commande du moteur Droite

//consigne en tour/s
//const float consigne_moteur_G = 0;//2;  // Consigne nombre de tours de roue par seconde moteur Gauche
    consigne_moteur_G = 0;//const float consigne_moteur_D = 0;//2;  // Consigne nombre de tours de roue par seconde moteur Droit
    consigne_moteur_D = 0;

    consigneNbTick_G = 0;
    consigneNbTick_D = 0;

// init calculs asservissement PID
    erreur_G_precedente = consigne_moteur_G; // (en tour/s)
    somme_erreur_G = 0;
    erreur_D_precedente = consigne_moteur_D; // (en tour/s)
    somme_erreur_D = 0;

    consigne_moteur_G = 0;
    consigne_moteur_D = 0;
    erreur_G_precedente = consigne_moteur_G; // (en tour/s)
    somme_erreur_G = 0;
    erreur_D_precedente = consigne_moteur_D; // (en tour/s)
    somme_erreur_D = 0;
    vitMoteur_G = 0;
    vitMoteur_D = 0;


    int distanceNbTick = distanceToNbTicks(distance);
    consigneNbTick_G = distanceNbTick;
    consigneNbTick_D = distanceNbTick;
    tick_codeuse_pos_G = tick_codeuse_pos_D = 0;

    String subDirectionInfo = direction.substring(direction.length()-4);
    Serial.println(subDirectionInfo);
    if(subDirectionInfo.compareTo("Wall") == 0){
        Serial.println("activating wall detector");
        enableWallDetector();
    }

    if (direction.compareTo("leftForward") == 0){
        motorStopped_G = false;
        motorStopped_D = true;
        directionFunction_L = motorForward_G;
        directionFunction_D = nothing;
    } else if (direction.compareTo("leftForwardWall") == 0){
        motorStopped_G = false;
        motorStopped_D = true;
        directionFunction_L = motorForward_G;
        directionFunction_D = nothing;
    } else if (direction.compareTo("rightForward") == 0){
        motorStopped_G = true;
        motorStopped_D = false;
        directionFunction_L = nothing;
        directionFunction_D = motorForward_D;
    } else if (direction.compareTo("rightForwardWall") == 0){
        motorStopped_G = true;
        motorStopped_D = false;
        directionFunction_L = nothing;
        directionFunction_D = motorForward_D;
    } if (direction.compareTo("leftBackward") == 0){
        motorStopped_G = false;
        motorStopped_D = true;
        directionFunction_L = motorBackWard_G;
        directionFunction_D = nothing;
    } else if (direction.compareTo("rightBackward") == 0){
        motorStopped_G = true;
        motorStopped_D = false;
        directionFunction_L = nothing;
        directionFunction_D = motorBackWard_D;
    }else if (direction.compareTo("forward") == 0) {
        motorStopped_G = false;
        motorStopped_D = false;
        directionFunction_L = motorForward_G;
        directionFunction_D = motorForward_D;
    } else if (direction.compareTo("forwardWall") == 0) {
        motorStopped_G = false;
        motorStopped_D = false;
        directionFunction_L = motorForward_G;
        directionFunction_D = motorForward_D;
    } else if (direction.compareTo("backward") == 0) {
        motorStopped_G = false;
        motorStopped_D = false;
        directionFunction_L = motorBackWard_G;
        directionFunction_D = motorBackWard_D;
    }else if (direction.compareTo("backwardWall") == 0){
        motorStopped_G = false;
        motorStopped_D = false;
        directionFunction_L = motorBackWard_G;
        directionFunction_D = motorBackWard_D;
    } else if (direction.compareTo("turnAroundLeft") == 0){
        motorStopped_G = false;
        motorStopped_D = false;
        directionFunction_L = motorBackWard_G;
        directionFunction_D = motorForward_D;
    } else if (direction.compareTo("turnAroundRight") == 0){
        motorStopped_G = false;
        motorStopped_D = false;
        directionFunction_L = motorForward_G;
        directionFunction_D = motorBackWard_D;
    }

    // Interruption sur tick de la codeuse du moteur Gauche  (interruption 0 = pin2 arduino)
    attachInterrupt(digitalPinToInterrupt(21), compteur_G, CHANGE);
    // Interruption sur tick de la codeuse du moteur Droit  (interruption 1 = pin3 arduino)
    attachInterrupt(digitalPinToInterrupt(20), compteur_D, CHANGE);

    // Interruption pour calcul du PID et asservissement appelee toutes les 10ms
    timerID = timer.setInterval(1000/frequence_echantillonnage, asservissement);

    bool change = false;
    while(!motorStopped_G || !motorStopped_D) {
        if (isWallDetectorEnabled) {
            if (isWall_L) {
                motorBreak_G();
                motorStopped_G = true;
                if(motorStopped_D) timer.disable(timerID);
                detachInterrupt(digitalPinToInterrupt(21));
                tick_codeuse_G = 0;
            }
            if (isWall_R) {
                Serial.println("roue droite");
                motorBreak_D();
                motorStopped_D = true;
                if(motorStopped_G) timer.disable(timerID);
                detachInterrupt(digitalPinToInterrupt(20));
                tick_codeuse_D = 0;
            }
        }
        if (isObstacle_AV) {
            motorBreak_G();
            motorBreak_D();
            delay(1000);
            change = false; // réactive rampe aceleration
            consigne_moteur_G = consigne_moteur_D = 0;
            if(!detectObstacle_AV()) isObstacle_AV = false;
        } else {
            timer.run();  //on fait tourner l'horloge
            delay(10);
            //*
            if (!change) {
                if (consigne_moteur_G < 1) consigne_moteur_G += 0.050;  // valeur bonne pour drapeau : 1.4
                if (consigne_moteur_D < 1) consigne_moteur_D += 0.050;  // valeur bonne pour drapeau : 1.35
            }
            if (consigne_moteur_G >= 1) change = true;
            //*/
            //*
            if (change) {
                if (tick_codeuse_pos_G >= consigneNbTick_G - 400 && consigne_moteur_G > 0.8) consigne_moteur_G -= 0.05;
                if (tick_codeuse_pos_D >= consigneNbTick_D - 400 && consigne_moteur_D > 0.8) consigne_moteur_D -= 0.05;
            }
            //*/
        }
    }
    if(subDirectionInfo.compareTo("Wall") == 0){
        disableWallDetector();
    }
}

#endif //TESTASSERVISSEMENTVITESSEANDPOSITIONNL_ASSERVISSEMENTMOTEURNLPERSO_H
