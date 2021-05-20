//#include <PinChangeIntConfig.h>
//#include <PinChangeInt.h>

//#include <AdaEncoder.h>

//#include <turnOffPWM.h>

//https://projetsdiy.fr/piloter-servomoteur-arduino/
#include <Servo.h>
// angle de 0° à 180°
// sens aiguille d'une montre 0 -> 180
// inverse 180 -> 0

Servo myservo;           // création de l'objet myservo 

//cable jaune sur 6
int pin_servo = 6;       // Pin 6 sur lequel est branché le servo sur l'Arduino si vous utilisez un ESP32 remplacez le 6 par 4 et si vous utilisez un ESP8266 remplacez le 6 par 2
int position = 95;       // Position souhaitée valeur testée : 70 mais pas bonne
int angle_depart = 140;
int angle_final = 0;
int increment = 5;

/* Carte Driver ..*/
/* Moteur Droite*/
const byte ENA=10;// PWM
const byte IN1=8;// Dir   1A
const byte IN2=9; // 2A

/* Moteur Gauche*/
const byte ENB=13;// PWM
const byte IN4=12;// Dir  1B
const byte IN3=11; // 2B

int vitesseENA = 80; // roue gauche
int vitesseENB = 110; // roue droite

void setup() {
  myservo.attach(pin_servo);  // attache le servo au pin spécifié sur l'objet 

  for(int i =8;i<14;i++)
  {
    pinMode(i,OUTPUT); // PINs en sortie
  }
  
  digitalWrite(IN1,0);
  digitalWrite(IN2,0);
  digitalWrite(IN3,0);
  digitalWrite(IN4,0);

  analogWrite(ENA,0);
  analogWrite(ENB,0);
}

void loop() {
  //Permet de choisir la position de l'angle de la "tige" 
  //myservo.write(angle_depart);
  //delay(2000);
  
  myservo.write(position);
  delay(1000);

  vitesseENA = 110; // roue gauche
  vitesseENB = 120;
  Backward(); //avance
  delay(7000);
  
  arret();
  delay(500);

  myservo.write(angle_depart);
  delay(10000);

  /*for (int pos = position; pos <= angle_depart; pos += increment) {
    myservo.write(pos);   
    delay(500);                       
  }
  delay(7000);*/
}

void arret()
{
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4, HIGH);
}

void Backward()
{
        digitalWrite(IN1,LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4, HIGH);
        analogWrite(ENA,vitesseENA);
        analogWrite(ENB,vitesseENB);
}

void Forward()
{
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENA,vitesseENA);
        analogWrite(ENB,vitesseENB);
}

void Turn_left()
{
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4, HIGH);
        analogWrite(ENA,vitesseENA);
}

void Turn_right()
{
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENB,vitesseENB);
}
