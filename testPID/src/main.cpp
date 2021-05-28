#include <Arduino.h>
const byte ENA = 7; // PWM         13
const byte IN1 = 8; // Dir   1A    12
const byte IN2 = 9; // 2A          11
int encoderPin = 2; //             18
unsigned int tick_codeuse = 0;     // Compteur de tick de la codeuse
unsigned int totalTick = 0;

volatile int tick_par_tour_codeuse = 64*50;
volatile int consigne_moteur_nombre_tours_par_seconde = 1;
volatile int kp = 200;
int cmd = 0;

//#include <SimpleTimer.h>           // http://arduino.cc/playground/Code/SimpleTimer
#include <MsTimer2.h>

//SimpleTimer timer;                 // Timer pour échantillonnage
const int frequence_echantillonnage = 50;  // Fréquence d'exécution de l'asservissement

/* Interruption sur tick de la codeuse */
void compteur(){
    tick_codeuse++;  // On incrémente le nombre de tick de la codeuse
    totalTick++;
}

/* Interruption pour calcul du PID */
void asservissement()
{
    // Calcul de l'erreur
    int frequence_codeuse = frequence_echantillonnage*tick_codeuse;
    float nb_tour_par_sec = (float)frequence_codeuse/(float)tick_par_tour_codeuse;
    float erreur = consigne_moteur_nombre_tours_par_seconde - nb_tour_par_sec;

    // Réinitialisation du nombre de tick de la codeuse
    tick_codeuse=0;

    // P : calcul de la commande
    cmd = kp*erreur;

    // Normalisation et contrôle du moteur
    if(cmd < 0) cmd = 0;
    else if(cmd > 255) cmd = 255;

    analogWrite(ENA, cmd);

    // DEBUG
    /*
    Serial.print(nb_tour_par_sec,8);
    Serial.print(" : ");
    Serial.print(erreur,4);
    Serial.println();
    //*/
}

/* Routine d'initialisation */
void setup() {
    Serial.begin(9600);         // Initialisation port COM
    pinMode(ENA, OUTPUT);   // Sortie moteur
    analogWrite(ENA, 0);  // Sortie moteur à 0
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    delay(2000);                // Pause de 5 sec pour laisser le temps au moteur de s'arréter si celui-ci est en marche

    attachInterrupt(digitalPinToInterrupt(encoderPin), compteur, CHANGE);    // Interruption sur tick de la codeuse  (interruption 0 = pin2 arduino mega)
    //timer.setInterval(1000/frequence_echantillonnage, asservissement);  // Interruption pour calcul du PID et asservissement
    MsTimer2::set(1000/frequence_echantillonnage, asservissement);
    MsTimer2::start();
}

/* Fonction principale */
void loop(){
    delay(1000);
    //timer.run();
    delay(10);
    //Serial.println(cmd);
}