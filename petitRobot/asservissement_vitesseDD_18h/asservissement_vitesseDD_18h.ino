#include <SimpleTimer.h>
#include <MsTimer2.h>

SimpleTimer timer;                 // Timer pour échantillonnage

//timer
bool isTimerSet = false;

unsigned int tick_codeuse_G = 0;     // Compteur de tick de la codeuse du moteur Gauche
unsigned int tick_codeuse_D = 0;     // Compteur de tick de la codeuse du moteur Droit
int vitMoteur_G = 0;                 // Commande du moteur Gauche
int vitMoteur_D = 0;                 // Commande du moteur Droite

const int frequence_echantillonnage = 100; // Fréquence d'exécution de l'asservissement
const int rapport_reducteur = 30;          // Rapport nombre de tours de l'arbre moteur et de la roue
const int tick_par_tour_codeuse = 32;  //64 tick sur deux capteurs hall, ici un seul capteur

//definition des entrées Moteur Gauche
const int motG_IN1 = 8;    // Commande de sens moteur, Input 1
const int motG_IN2 = 7;    // Commande de sens moteur, Input 2
const int pinPowerG  = 9;    // Commande de vitesse moteur, Output Enabled1

//definition des entrées Moteur Droite
const int motD_IN3 = 12;    // Commande de sens moteur, Input 1
const int motD_IN4 = 13;    // Commande de sens moteur, Input 2
const int pinPowerD  = 11;    // Commande de vitesse moteur, Output Enabled1

//consigne en tour/s
//const float consigne_moteur_G = 0;//2;  // Consigne nombre de tours de roue par seconde moteur Gauche
float consigne_moteur_G = 0;
//const float consigne_moteur_D = 0;//2;  // Consigne nombre de tours de roue par seconde moteur Droit
float consigne_moteur_D = 0;

// init calculs asservissement PID
float erreur_G_precedente = consigne_moteur_G; // (en tour/s)
float somme_erreur_G = 0;
float erreur_D_precedente = consigne_moteur_D; // (en tour/s)
float somme_erreur_D = 0;

//Definition des constantes du correcteur PID
//const float kp = 1000; // Coefficient proportionnel (choisis par essais successifs)
const float kpG = 1000;  // Coefficient proportionnel du moteur gauche
const float kpD = 1000;  // Coefficient proportionnel du moteur droit
const float kiG = 20; //5;   // Coefficient intégrateur
const float kiD = 20;
const float kdG = 0; //100; // Coefficient dérivateur
const float kdD = 0;

/* Routine d'initialisation */
void setup()
{
    Serial.begin(115200);         // Initialisation port COM

    MsTimer2::set(3500, finRun);
    
    pinMode(pinPowerG, OUTPUT);    // Sorties commande moteur
    pinMode( motG_IN1, OUTPUT );
    pinMode( motG_IN2, OUTPUT );

    analogWrite(pinPowerG, 0);  // Initialisation sortie moteur à 0
    delay(300);                // Pause de 0,3 sec pour laisser le temps au moteur de s'arréter si celui-ci est en marche

    // Interruption sur tick de la codeuse du moteur Gauche  (interruption 0 = pin2 arduino)
    attachInterrupt(0, compteur_G, CHANGE);

    // Interruption sur tick de la codeuse du moteur Droit  (interruption 1 = pin3 arduino)
    attachInterrupt(1, compteur_D, CHANGE);

    // Interruption pour calcul du PID et asservissement appelee toutes les 10ms
    timer.setInterval(1000/frequence_echantillonnage, asservissement);
}

/* Fonction principale */
void loop()
{
   if(!isTimerSet){
        MsTimer2::start();
        isTimerSet = true;
    }
    
    timer.run();  //on fait tourner l'horloge
    delay(10);
    if(consigne_moteur_D < 3 && consigne_moteur_G < 3){
      consigne_moteur_D += 0.025;
      consigne_moteur_G += 0.025;
    }
}

//---- Interruption sur tick de la codeuse du moteur Gauche
void compteur_G()
{
    tick_codeuse_G++;
    // On incrémente le nombre de tick de la codeuse.   un seul sens
}

//---- Interruption sur tick de la codeuse du moteur Droit
void compteur_D()
{
    tick_codeuse_D++;
    // On incrémente le nombre de tick de la codeuse.   un seul sens
}

//---- Interruption pour calcul du P
void asservissement()
{
    // Calcul de l'erreur_G
    int frequence_codeuse_G = frequence_echantillonnage * tick_codeuse_G; //100*tick_codeuse_G
    int frequence_codeuse_D = frequence_echantillonnage * tick_codeuse_D; //100*tick_codeuse_G
    
    float vit_roue_tour_sec_G = (float)frequence_codeuse_G / (float)tick_par_tour_codeuse / (float)rapport_reducteur;    //(100*tick_codeuse_G)/32/19
    float vit_roue_tour_sec_D = (float)frequence_codeuse_D / (float)tick_par_tour_codeuse / (float)rapport_reducteur;    //(100*tick_codeuse_G)/32/19   
    
    float erreur_G = (consigne_moteur_G) - vit_roue_tour_sec_G; // pour le proportionnel
    float erreur_D = (consigne_moteur_D) - vit_roue_tour_sec_D; // pour le proportionnel
    
    somme_erreur_G += erreur_G; // pour l'intégrateur
    somme_erreur_D += erreur_D; // pour l'intégrateur
    
    float delta_erreur_G = erreur_G - erreur_G_precedente;  // pour le dérivateur
    erreur_G_precedente = erreur_G;
    float delta_erreur_D = erreur_D - erreur_D_precedente;  // pour le dérivateur
    erreur_D_precedente = erreur_D;
    

    // Réinitialisation du nombre de tick des  codeuses
    tick_codeuse_G = 0;
    tick_codeuse_D = 0;

    // P : calcul de la commande
    vitMoteur_G = kpG*erreur_G + kiG*somme_erreur_G + kdG*delta_erreur_G;  //somme des trois erreur_Gs
    vitMoteur_D = kpD*erreur_D + kiD*somme_erreur_D + kdD*delta_erreur_D;  //somme des trois erreur_Gs

    // Normalisation et contrôle du moteur de Gauche
    if ( vitMoteur_G > 255 )
    {
        vitMoteur_G = 255;  // sachant que l'on est branché sur un pont en H L293D
    }
    else if ( vitMoteur_G < 0 )
    {
        vitMoteur_G = 0;
    }

     // Normalisation et contrôle du moteur de Droite
    if ( vitMoteur_D > 255 )
    {
        vitMoteur_D = 255;  // sachant que l'on est branché sur un pont en H L293D
    }
    else if ( vitMoteur_D < 0 )
    {
        vitMoteur_D = 0;
    }

    TournerDroite_G(vitMoteur_G);
    TournerDroite_D(vitMoteur_D);

    // DEBUG
    Serial.print(vit_roue_tour_sec_G);  // affiche à gauche la vitesse et à droite l'erreur_G
    Serial.print(" : ");
    Serial.print(vit_roue_tour_sec_D);  // affiche à gauche la vitesse et à droite l'erreur_D
    //Serial.print(" : ");
    //Serial.print(erreur_G, 4);
    //Serial.print(" : ");
    //Serial.print(vitMoteur_G);
    Serial.println();
}

//---- fonction pour faire tourner le moteur dans un sens (a droite)
void TournerDroite_G( int powerRate )
{
    digitalWrite(motG_IN1, HIGH);
    digitalWrite(motG_IN2, LOW);
    analogWrite(pinPowerG, powerRate);
}

void TournerDroite_D( int powerRate )
{
    digitalWrite(motD_IN3, HIGH);
    digitalWrite(motD_IN4, LOW);
    analogWrite(pinPowerD, powerRate);
}

void finRun()
{
    digitalWrite(motG_IN1, HIGH);
    digitalWrite(motG_IN2, HIGH);
    digitalWrite(motD_IN3, HIGH);
    digitalWrite(motD_IN4, HIGH);
    while(1);
}
