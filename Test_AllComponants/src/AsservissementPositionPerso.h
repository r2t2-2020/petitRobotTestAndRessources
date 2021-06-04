//
// Created by gozlanp on 04/06/2021.
//
#include <SimpleTimer.h>
#include <digitalWriteFast.h>

#ifndef TEST_ALLCOMPONANTS_ASSERVISSEMENTPOSITIONPERSO_H
#define TEST_ALLCOMPONANTS_ASSERVISSEMENTPOSITIONPERSO_H

SimpleTimer timer;                 // Timer pour échantillonnage

bool fin = false;
//init echantillonage
unsigned int time = 0;
const int frequence_echantillonnage = 50;

//init compteur :
int encoder0PosA = 0; //position de départ=0
int lastReportedPosA = 0;
int encoder0PosB = 0; //position de départ=0
int lastReportedPosB = 0;

boolean A_set = false;
boolean B_set = false;

boolean C_set = false;
boolean D_set = false;

//Consigne
int target_ticksA = (1920*3);
int target_ticksB = 1920*3;

// init calculs asservissement PID
int erreurA = 0; //erreur
int erreurPrecedenteA = 0;
int somme_erreurA = 0;

int erreurB = 0; //erreur
int erreurPrecedenteB = 0;
int somme_erreurB = 0;

//Definition des constantes du correcteur PID
//moteur gauche
const float kpA = 1;  // Coefficient proportionnel (choisis par essais successifs)
const float kiA = 0.0001;   // Coefficient intégrateur
const float kdA = 3.45;   // Coefficient dérivateur 3.45

//moteur droite
const float kpB = 1;  // Coefficient proportionnel (choisis par essais successifs)
const float kiB = 0.0001;   // Coefficient intégrateur
const float kdB = 3.3;   // Coefficient dérivateur 3.45

int timer_ID = 0;

//---- Cette fonction est appelée toutes les 20ms pour calcul du correcteur PID
void asservissement()
{
    time += 20; // pratique pour graphes excel après affichage sur le moniteur

    erreurA = target_ticksA - encoder0PosA;
    erreurB = target_ticksB - encoder0PosB;

    if(erreurA <= 10 && erreurB <= 10){
        fin = true;
    }

    somme_erreurA += erreurA;
    somme_erreurB += erreurB;

    float vitMoteurA = kpA * erreurA + kdA * (erreurA - erreurPrecedenteA) + kiA * (somme_erreurA);
    float vitMoteurB = kpB * erreurB + kdB * (erreurB - erreurPrecedenteB) + kiB * (somme_erreurB);
    //Serial.println(vitMoteur);

    erreurPrecedenteA = erreurA;
    erreurPrecedenteB = erreurB;

    // Normalisation et contrôle du moteur
    if ( vitMoteurA > 200 ) vitMoteurA = 200;  // on est branché sur un pont en H L293D
    else if ( vitMoteurA < -200 ) vitMoteurA = -200;

    if ( vitMoteurB > 200 ) vitMoteurB = 200;  // on est branché sur un pont en H L293D
    else if ( vitMoteurB < -200 ) vitMoteurB = -200;

    TournerA (vitMoteurA);
    TournerB (vitMoteurB);

    /*Serial.print(time);
    Serial.print(" ");*/
    Serial.print(encoder0PosA);
    Serial.print(" ");
    Serial.print(encoder0PosB);
    Serial.print(" ");
    Serial.println(target_ticksB);
    //Serial.println(
}

//---- Interruption appelée à tous les changements d'état de A
void doEncoderA()
{
    /*A_set = digitalReadFast2(encoderPinA) == HIGH;
    encoder0Pos += (A_set != B_set) ? -1 : 1 ;*/ //modifie le compteur selon les deux états des encodeurs
    if (digitalReadFast2(encoderPinA) == digitalReadFast2(encoderPinB)) {
        encoder0PosA++;
    }
    else {
        encoder0PosA--;
    }

}

//---- Interruption appelée à tous les changements d'état de B
void doEncoderB()
{
    if (digitalReadFast2(encoderPinA) == digitalReadFast2(encoderPinB)) {
        encoder0PosA--;
    }
    else {
        encoder0PosA++;
    }
}

void doEncoderC()
{
    /*A_set = digitalReadFast2(encoderPinA) == HIGH;
    encoder0Pos += (A_set != B_set) ? -1 : 1 ;*/ //modifie le compteur selon les deux états des encodeurs
    if (digitalReadFast2(encoderPinC) == digitalReadFast2(encoderPinD)) {
        encoder0PosB--;
    }
    else {
        encoder0PosB++;
    }

}

//---- Interruption appelée à tous les changements d'état de B
void doEncoderD()
{
    if (digitalReadFast2(encoderPinC) == digitalReadFast2(encoderPinD)) {
        encoder0PosB++;
    }
    else {
        encoder0PosB--;
    }
}
//---- Fonction appelée pour contrôler le moteur
void TournerA( int vitesse )
{
    if ( vitesse > 0 )
    {
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
    }
    else
    {
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        vitesse = -vitesse;
    }

    analogWrite(ENA, vitesse);
}

void TournerB( int vitesse )
{
    if ( vitesse > 0 )
    {
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
    }
    else
    {
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        vitesse = -vitesse;
    }

    analogWrite(ENB, vitesse);
}

#endif //TEST_ALLCOMPONANTS_ASSERVISSEMENTPOSITIONPERSO_H
