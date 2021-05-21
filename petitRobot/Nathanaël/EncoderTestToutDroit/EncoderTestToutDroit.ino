#include <Encoder.h>

//https://projetsdiy.fr/piloter-servomoteur-arduino/
#include <Servo.h>
// angle de 0° à 180°
// sens aiguille d'une montre 0 -> 180
// inverse 180 -> 0

Servo myservo;           // création de l'objet myservo 

//cable jaune sur 6
int pin_servo = 6;       // Pin 6 sur lequel est branché le servo sur l'Arduino si vous utilisez un ESP32 remplacez le 6 par 4 et si vous utilisez un ESP8266 remplacez le 6 par 2
int position = 70;       // Position souhaitée
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



Encoder encoderLeft(2, 3);  // encoder
Encoder encoderRight(18, 19);  // encoder
long oldPositionLeft  = -999; //encoder
long oldPositionRight;  // encoder

void setup() {
  Serial.begin(115200);
  Serial.println("Basic Encoder Test:");
  attachInterrupt(digitalPinToInterrupt(2), encoderReadLeft, CHANGE);
  attachInterrupt(digitalPinToInterrupt(18), encoderReadRight, CHANGE);
  
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

void encoderReadLeft(){
   oldPositionLeft = encoderLeft.read();
   if(oldPositionLeft > oldPositionRight){
    vitesseENA--;
   }
}

void encoderReadRight(){
   oldPositionRight = encoderRight.read();
   if(oldPositionRight > oldPositionLeft){
    vitesseENB--;
   }
}

void encoderReadTest(){
   long newPosition = encoderRight.read();
  if (newPosition != oldPositionRight) {
    oldPositionRight = newPosition;
    Serial.println(newPosition);
  }
}

void loop() {
  Backward(); //avance
  delay(7000);
  
  arret();
  delay(500);
  
  

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
