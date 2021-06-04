#include <SimpleTimer.h>
#include <digitalWriteFast.h> 
//30 pour 1 et 64 cpr
// 32.27 cm en un tour de roue
//Résolution vitesse pour une période d'échantillonage de 10ms:1,734cm/s 

SimpleTimer timer;                 // Timer pour échantillonnage

bool fin = false;

//106mm diam=10.6cm
//definition des entrées
//moteur gauche
const int pinPowerA  = 7;    // Commande de vitesse moteur, Output Enabled1
const int pinInput1 = 8;    // Commande de sens moteur, Input 1
const int pinInput2 = 9;    // Commande de sens moteur, Input 2
const int encoderPinA = 18;    // compteur 1
const int encoderPinB = 19;    // compteur 2

//moteur droite
const int pinPowerB  = 13;    // Commande de vitesse moteur, Output Enabled1
const int pinInput3 = 11;    // Commande de sens moteur, Input 1
const int pinInput4 = 12;    // Commande de sens moteur, Input 2
const int encoderPinC = 2;    // compteur 1
const int encoderPinD = 3;    // compteur 2

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

/* Routine d'initialisation */
void setup()
{
   //target_ticks = target_deg / 360.0 * 30.0 * 64.0;
   
    Serial.begin(115200);         // Initialisation port COM

    //gauche
    pinMode(pinPowerA, OUTPUT);   // Sorties commande  moteur
    pinMode(pinInput1, OUTPUT);
    pinMode(pinInput2, OUTPUT);
    pinMode(encoderPinA, INPUT);  //sorties encodeur
    pinMode(encoderPinB, INPUT);
    
    //droite
    pinMode(pinPowerB, OUTPUT);   // Sorties commande  moteur
    pinMode(pinInput3, OUTPUT);
    pinMode(pinInput4, OUTPUT);
    pinMode(encoderPinC, INPUT);  //sorties encodeur
    pinMode(encoderPinD, INPUT);

    attachInterrupt(digitalPinToInterrupt(2), doEncoderA, CHANGE);
    attachInterrupt(digitalPinToInterrupt(3), doEncoderB, CHANGE);
    
    attachInterrupt(digitalPinToInterrupt(18), doEncoderC, CHANGE);
    attachInterrupt(digitalPinToInterrupt(19), doEncoderD, CHANGE);

    analogWrite(pinPowerA, 0);
    analogWrite(pinPowerB, 0);
    delay(300);                

    // Interruption pour calcul du PID et asservissement appelée toutes les 10ms
    timer_ID = timer.setInterval(1000 / frequence_echantillonnage, asservissement);
}
    int cpt = 0;
/* Fonction principale */
void loop()
{
    timer.run();  //on fait tourner l'horloge
    delay(20);
    
    if(fin){
      timer.disable(timer_ID);
      analogWrite(pinPowerA, 0);
      analogWrite(pinPowerB, 0);

      if(cpt < 3){
      delay(3000);

      timer.enable(timer_ID);

      encoder0PosA = 0;
      encoder0PosB = 0;
      target_ticksA = (1920*1);
      target_ticksB = (1920*1);
      fin = false;
      cpt++;
      }
    }
}

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
    Serial.print(target_ticksA);
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
        digitalWrite(pinInput1, LOW);
        digitalWrite(pinInput2, HIGH);
    }
    else
    {
        digitalWrite(pinInput1, HIGH);
        digitalWrite(pinInput2, LOW);
        vitesse = -vitesse;
    }

    analogWrite(pinPowerA, vitesse);
}

void TournerB( int vitesse )
{
    if ( vitesse > 0 )
    {
        digitalWrite(pinInput3, LOW);
        digitalWrite(pinInput4, HIGH);
    }
    else
    {
        digitalWrite(pinInput3, HIGH);
        digitalWrite(pinInput4, LOW);
        vitesse = -vitesse;
    }

    analogWrite(pinPowerB, vitesse);
}
