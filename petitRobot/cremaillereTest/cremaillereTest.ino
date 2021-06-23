// Cette librairie permet à une carte Arduino de contrôler des servomoteurs

//https://www.norwegiancreations.com/2017/09/arduino-tutorial-using-millis-instead-of-delay/ POUR REMPLACER DELAY PAR MILLIS
/*#include <Servo.h> 

// Crée un objet de type "Servo", nommé -> rouedroite
Servo cremaillere;

int arret = 1510;

// variable vitesse et de direction pour le servomoteur 
int temps = 0;

// Declaration de la variable pour la rampe de demarrage
int valeur_de_vitesse_demarrage;


// Declaration de la variable pour la vitesse rampe de demarrage
// unsigned long-> déclare une variable de type long non signé
unsigned long rampedemarrage = millis();

void setup() {

  //  initialisation de la connexion série
  // IMPORTANT : la fenêtre terminal côté PC doit être réglée sur la même valeur.  
  Serial.begin(9600);

  // associe la variable rouedroite a sa broche en autre la numero 3   
  cremaillere.attach(2);

 // Écrit une valeur en microsecondes (uS) sur le servo, 
 // la valeur par defaut etant 1500 ce qui correspond en
 // general à l'arret
 cremaillere.writeMicroseconds(arret);   
 

}


 //Le programme principal s’exécute par une boucle infinie appelée Loop () 
 
 
void loop() {

 // valeur de la base de temps 1 -> 1000ms soit 1 seconde
 // la ligne if  effectue la difference entre le temps actuel et le 
 // temps de debut de boucle .Cette derniere n'est interrompue que lorsque 
 // cette différence = 100 millisecondes  
 if ((millis ()-rampedemarrage>100)& ( valeur_de_vitesse_demarrage <= 100))
 
 {
 rampedemarrage=millis();
 // incrementation de la variable valeur de 1 soit -> valeur = valeur+1
 valeur_de_vitesse_demarrage ++;
 
 Serial.print("valeur de la vitesse de demarrage =>"); 
 Serial.print(valeur_de_vitesse_demarrage);
 Serial.print(" valeur de la pente de demarrage =>");
 Serial.println(temps);
 }



 temps= valeur_de_vitesse_demarrage + arret ;  
 // envoie de la valeur au servomoteur pour la rotation ou l'arret
 cremaillere.writeMicroseconds(temps);

}
*/
#include <Servo.h>

Servo myservo;  // création de l'objet myservo 

int pin_servo = 2;       // Pin 6 sur lequel est branché le servo sur l'Arduino si vous utilisez un ESP32 remplacez le 6 par 4 et si vous utilisez un ESP8266 remplacez le 6 par 2

//int pos = 0;             // variable permettant de conserver la position du servo
//int angle_initial = 0;   //angle initial
//int angle_final = 180;   //angle final
//int increment = 5;       //incrément entre chaque position
//bool angle_actuel = true;//Envoi sur le port série la position courante du servomoteur

void setup() {
  /*int vitesse = 200;
int duree = 800;*/
  Serial.begin(9600);                       
  while(!Serial){;} 
  myservo.attach(pin_servo);  // attache le servo au pin spécifié sur l'objet myservo
  
}
int arret = 1510;
int vitesse = 200;
int duree = 800;

void loop() {
  myservo.write(arret);
  delay(1000);

  myservo.write(arret-vitesse);
  delay(duree);

  myservo.write(arret);
  delay(1000);

  myservo.write(arret+vitesse);
  delay(duree);

  myservo.write(arret);
  delay(1000);

  myservo.write(arret+vitesse);
  delay(duree);

  myservo.write(arret);
  delay(1000);

  myservo.write(arret-vitesse);
  delay(duree);
  
  myservo.write(arret);
  delay(1000);

}
