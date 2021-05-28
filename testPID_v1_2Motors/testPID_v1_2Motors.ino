 /* Modification du code pour adaptation Mega2560*/
 /* 28 mai 21*/
// Carte Mega2560:
// PIND:X X X X INT3(18) INT2(19) INT1(20) INT0(21)


#include <PID_v1.h>   // Pour le PID
#include <TimerOne.h> // Pour le timer

// commande du moteur droit MàJ
#define ENCODEURDROITA 21             // sur INT0
#define ENCODEURDROITB 20             // sur INT1
#define ENCODEURDROITA_PINDPOS 0      // Position du bit correspondant à INT0 dans le registre PIND
#define ENCODEURDROITB_PINDPOS 1
#define MOTEURDROIT_ENA 7             // contrôle vitesse moteur droit; PWM
#define MOTEURDROIT_IN1 8             // controle direction moteur droit IN1
#define MOTEURDROIT_IN2 9             // controle direction moteur droit IN2

// commande du moteur Gauche MàJ
#define ENCODEURGAUCHEA 19            // sur INT2
#define ENCODEURGAUCHEB 18            // sur INT3
#define ENCODEURGAUCHEA_PINDPOS 2     // Position du bit correspondant à INT2 dans le registre PIND
#define ENCODEURGAUCHEB_PINDPOS 3
#define MOTEURGAUCHE_ENB 13              // contrôle vitesse moteur gauche; PWM
#define MOTEURGAUCHE_IN3 12              // controle direction moteur gauche IN3
#define MOTEURGAUCHE_IN4 11              // controle direction moteur gauche IN4

double SetpointDroit, InputDroit, OutputDroit; // A vérifier Consigne, vitesse?, PWM??
double SetpointGauche, InputGauche, OutputGauche;

double KpGauche = 1.5; // 1.5; 
double KiGauche = 4;//4;
double Kd = 0.1;

double KpDroit = 0.8;// 0.8;
double KiDroit = 3;//4;

PID PIDDROIT(&InputDroit, &OutputDroit, &SetpointDroit, KpDroit, KiDroit, Kd, DIRECT); // From PID_v1.h
PID PIDGAUCHE(&InputGauche, &OutputGauche, &SetpointGauche, KpGauche, KiGauche, Kd, DIRECT);

// volatile => pour toute variable qui seront utilisées dans les interruptions
volatile int16_t countDroit = 0; /* comptage de tick d'encodeur qui sera incrémenté sur interruption " On change " sur l'interruption INT0  max 32767 attention à l'overflow*/
volatile int16_t countGauche = 0; /* comptage de tick d'encoder qui sera incrémenté sur interruption " On change " sur l'interruption INT2 max 32767 attention à l'overflow */
volatile double speedDroit = 0; // vitesse du moteur
volatile double speedGauche = 0; // vitesse du moteur

unsigned long time0 = 0; // stock un temps à un instant donné
unsigned long timer = 0; // variable qui va contenir le dernier temps enregistré via millis

int8_t valeur = 20;  // lecture de la consigne via le moniteur serie pour test, initialisé à 40 pour test rapide du PID

void setup()
{
  //initialisation moniteur serie
  Serial.begin(9600);       // facultatif uniquement pour feedback
  Serial.println("cool");
  // on initialise les entrées et sorties
  pinMode(ENCODEURDROITA, INPUT_PULLUP);
  pinMode(ENCODEURDROITB, INPUT_PULLUP);
  pinMode(ENCODEURGAUCHEA, INPUT_PULLUP);
  pinMode(ENCODEURGAUCHEB, INPUT_PULLUP);

  pinMode(MOTEURDROIT_ENA, OUTPUT);
  pinMode(MOTEURDROIT_IN1, OUTPUT);
  pinMode(MOTEURDROIT_IN2, OUTPUT);
  pinMode(MOTEURGAUCHE_ENB, OUTPUT);
  pinMode(MOTEURGAUCHE_IN3, OUTPUT);
  pinMode(MOTEURGAUCHE_IN4, OUTPUT);

  // moteurs à l'arret
  stopMotors();

  // Encoder quadrature counter
  attachInterrupt(ENCODEURDROITA_PINDPOS, counterDroit, CHANGE); // lorsqu'il y une modification sur le pin 21, on interrompte le programme pour enclencher le comptage
  attachInterrupt(ENCODEURGAUCHEA_PINDPOS, counterGauche, CHANGE); // lorsqu'il y une modification sur le pin 19, on interrompte le programme pour enclencher le comptage

  Timer1.initialize(80000);        // set a timer of length  0.08 sec => permet d'avoir speed le plus proche de 32767 sans dépasser 32767 en vitesse max ! 
  Timer1.attachInterrupt( timerIsr );

  // PID
  InputDroit = 0;
  SetpointDroit = 0;
  InputGauche = 0;
  SetpointGauche = 0;
  //active le PID
  PIDDROIT.SetMode(AUTOMATIC);
  PIDDROIT.SetOutputLimits(-255, 255);
  PIDGAUCHE.SetMode(AUTOMATIC);
  PIDGAUCHE.SetOutputLimits(-255, 255);
}

void loop() {
  //while(1){test();}
  if (Serial.available()) {
    time0 = timer;
    valeur = Serial.parseInt(); //récupération des caractères sur le port série
    Serial.println(valeur);
  }
  if (valeur != 0) {
    runMotorSpeed(valeur, valeur);
  } else {
    //stopMotors();
  }
  timer = millis();
  /*
  if ( (timer - time0) > 90000) { //Timeout !
    valeur = 0 ;
    stopMotors();
    time0 = timer;
  }
  //*/

  /*
  Serial.println("speedDroit");
  Serial.println(speedDroit);                 // à commenter, utilisé pour débug
  Serial.println("speedGauche");
  Serial.println(speedGauche);                 // à commenter, utilisé pour débug
  Serial.println("'''''''''''''''''");    // à commenter, utilisé pour débug
  //*/
}



void counterDroit()
{
  byte state = PIND;
  (((state >> ENCODEURDROITA_PINDPOS) & 1) ^ ((state >> ENCODEURDROITB_PINDPOS) & 1)) ? countDroit-- : countDroit++; // régler ++ et -- pour que faire avancer => +
}

// Encoder counter 2

void counterGauche()
{
  byte state = PIND;
  (((state >> ENCODEURGAUCHEA_PINDPOS) & 1 ) ^ ((state >> ENCODEURGAUCHEB_PINDPOS) & 1)) ? countGauche-- : countGauche++; // régler ++ et -- pour que faire avancer => +
}


// Timer pour calculer la vitesse grace aux encodeurs

void timerIsr() {
  speedDroit = countDroit;
  countDroit = 0;
  speedGauche = countGauche;
  countGauche = 0;
}

void stopMotors() {
  digitalWrite(MOTEURDROIT_IN1, HIGH);
  digitalWrite(MOTEURDROIT_IN2, HIGH);
  digitalWrite(MOTEURGAUCHE_IN3, HIGH);
  digitalWrite(MOTEURGAUCHE_IN4, HIGH);
}


void test() {
  // Moteur droit avance
  digitalWrite(MOTEURDROIT_IN1, LOW);
  digitalWrite(MOTEURDROIT_IN2, HIGH);
  // Moteur gauche avance
  digitalWrite(MOTEURGAUCHE_IN3, LOW);
  digitalWrite(MOTEURGAUCHE_IN4, HIGH);
  /*
  Serial.print("speedDroit : ");
  Serial.println(speedDroit);                 // à commenter, utilisé pour débug
  Serial.print("speedGauche : ");
  Serial.println(speedGauche);                 // à commenter, utilisé pour débug
  Serial.println("'''''''''''''''''");    // à commenter, utilisé pour débug
  //*/
}

void avancerMoteurDroit(uint8_t a) // En avant
{
  analogWrite (MOTEURDROIT_ENA, a); // Contrôle de vitesse en PWM, moteur 1
  digitalWrite(MOTEURDROIT_IN1, LOW);
  digitalWrite(MOTEURDROIT_IN2, HIGH);
}
void avancerMoteurGauche(uint8_t a) // En avant
{
  analogWrite (MOTEURGAUCHE_ENB, a); // Contrôle de vitesse en PWM, moteur 2
  digitalWrite(MOTEURGAUCHE_IN3, LOW);
  digitalWrite(MOTEURGAUCHE_IN4, HIGH);
}

void reculerMoteurDroit (uint8_t a) // En arrière
{
  analogWrite (MOTEURDROIT_ENA, a); // Contrôle de vitesse en PWM, moteur 1
  digitalWrite(MOTEURDROIT_IN1, HIGH);
  digitalWrite(MOTEURDROIT_IN2, LOW);
}
void reculerMoteurGauche (uint8_t a) // En arrière
{
  analogWrite (MOTEURGAUCHE_ENB, 255-a); // Contrôle de vitesse en PWM, moteur 2
  digitalWrite(MOTEURGAUCHE_IN3, HIGH);
  digitalWrite(MOTEURGAUCHE_IN4, LOW);
}


void runMotorSpeed( int8_t commandeMoteurDroit, int8_t commandeMoteurGauche) {

  SetpointDroit = commandeMoteurDroit;
  SetpointGauche = commandeMoteurGauche;

  InputDroit = speedDroit;
  InputGauche = speedGauche;

  PIDDROIT.Compute();
  PIDGAUCHE.Compute();

  int outputDroit = (int)OutputDroit;
  int outputGauche = (int)OutputGauche;

  //utilisation de la sortie du PID pour asservir les moteurs
  if (outputDroit >= 0) {
    avancerMoteurDroit(outputDroit);
  }
  if (outputDroit < 0) {
    reculerMoteurDroit(-outputDroit);
  }
  if (outputGauche >= 0) {
    avancerMoteurGauche(outputGauche);
  }
  if (outputGauche < 0) {
    reculerMoteurGauche(-outputGauche);
  }
  // à commenter, utilisé pour débug
  /*
  Serial.println("output1");
  Serial.println(outputDroit);                
  Serial.println("output2");
  Serial.println(outputGauche);                
  Serial.println("'''''''''''''''''");  
  //*/      
}
