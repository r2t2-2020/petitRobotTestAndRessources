//https://projetsdiy.fr/piloter-servomoteur-arduino/
#include <Servo.h>

Servo myservo;  // création de l'objet myservo 

int pin_servo = 2;       // Pin 6 sur lequel est branché le servo sur l'Arduino si vous utilisez un ESP32 remplacez le 6 par 4 et si vous utilisez un ESP8266 remplacez le 6 par 2

/*int pos = 0;             // variable permettant de conserver la position du servo
int angle_initial = 0;   //angle initial
int angle_final = 180;   //angle final
int increment = 5;       //incrément entre chaque position
bool angle_actuel = true;//Envoi sur le port série la position courante du servomoteur
*/
void setup() {
  Serial.begin(9600);                       
  while(!Serial){;} 
  myservo.attach(pin_servo);  // attache le servo au pin spécifié sur l'objet myservo
  
}
int arret = 1510;
int vitesse = 200;
int duree = 900;

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
 /* myservo.write(1510);
  delay(1000);

  myservo.write(1000);
  delay(1200);*/
}
