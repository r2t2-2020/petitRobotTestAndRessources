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
int angle_depart = 180;
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

volatile int vitesseENA = 80; // roue gauche
volatile int vitesseENB = 110; // roue droite

bool run = true;  // savoir si on avance



Encoder encoderLeft(18, 19);
Encoder encoderRight(2, 3);
volatile long posLeft = 0;
volatile long posRight = 0;
volatile long commandLeft = -9999;
volatile long commandRight = -9999;

void setup() {
  Serial.begin(9600);
  Serial.println("Test de régulation avec encodeur");
  //attachInterrupt(digitalPinToInterrupt(2), encoderReadRight, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(18), encoderReadLeft, CHANGE);
  
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
  if(encoderLeft.read() >= commandLeft){
    detachInterrupt(digitalPinToInterrupt(18));
    stopLeft();
  }
}

void encoderReadRight(){
  if(encoderRight.read() >= commandRight){
    detachInterrupt(digitalPinToInterrupt(2));
    stopRight();
  }
}


void loop() {
  if(run){
    //Forward(2068); // avance un tour
    Forward(30650);  // avance 10 tours
    //Forward(3065);
    //Forward(2068); //avance
    run = false;
  }
  
  Serial.print("posRight: ");
  Serial.println(posRight);
  Serial.print(", vitesseENB: ");
  Serial.println(vitesseENB);

  /*for (int pos = position; pos <= angle_depart; pos += increment) {
    myservo.write(pos);   
    delay(500);                       
  }
  delay(7000);*/
}

void stopRight()
{
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
}

void stopLeft()
{
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, HIGH);
}

void arret()
{
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, HIGH);
}

void Forward(long nbImpulsion)
{
        encoderLeft.write(0);
        encoderRight.write(0);
        commandLeft = nbImpulsion;
        commandRight = nbImpulsion;
        attachInterrupt(digitalPinToInterrupt(18), encoderReadLeft, CHANGE);
        attachInterrupt(digitalPinToInterrupt(2), encoderReadRight, CHANGE);
        digitalWrite(IN1,LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4, HIGH);
        analogWrite(ENA,vitesseENA);
        analogWrite(ENB,vitesseENB);
}

void Backward()
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
