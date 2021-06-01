//https://projetsdiy.fr/piloter-servomoteur-arduino/
#include <Servo.h>

Servo myservo;  // création de l'objet myservo 

int pin_servo = 2;       // Pin 6 sur lequel est branché le servo sur l'Arduino si vous utilisez un ESP32 remplacez le 6 par 4 et si vous utilisez un ESP8266 remplacez le 6 par 2

int pos = 0;             // variable permettant de conserver la position du servo
int angle_initial = 0;   //angle initial
int angle_final = 180;   //angle final
int increment = 5;       //incrément entre chaque position
bool angle_actuel = true;//Envoi sur le port série la position courante du servomoteur

void setup() {
  Serial.begin(9600);                       
  while(!Serial){;} 
  myservo.attach(pin_servo);  // attache le servo au pin spécifié sur l'objet myservo
  
}

void loop() {
  for (pos = angle_initial; pos <= angle_final; pos += increment) { // Déplace le servo de 0 à 180 degréespar pas de 1 degrée 
    myservo.write(pos);              // Demande au servo de se déplacer à cette position angulaire
    delay(30);                       // Attend 30ms entre chaque changement de position
    if (angle_actuel) {
        Serial.println(myservo.read());
    
    }
  }
  for (pos = angle_final; pos >= angle_initial; pos -= increment) { // Fait le chemin inverse
    myservo.write(pos);              
    delay(30);   
    if (angle_actuel) {
        Serial.println(myservo.read());
    }
  }
}
