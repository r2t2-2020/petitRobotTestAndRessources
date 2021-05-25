#include <Servo.h>
#include <SharpIR.h>
#include <MsTimer2.h>

/*
orange 0
jaune 1
vert 2
bleu 3
*/

//tirette 
const int pin_tirette = 4;
bool isTimerSet = false;

// telemetre
int ArG; // 0 quand leds allumées == obstacle détecté
int ArD;
int pin_ArG = 4;
int pin_ArD = 5;

// Encoder
Encoder encoderLeft(18, 19);
Encoder encoderRight(2, 3);
volatile long posLeft = 0;
volatile long posRight = 0;
volatile long commandLeft = -9999;
volatile long commandRight = -9999;

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


/*bool isObstacleArG = false;
bool isObstacleArD = false;
int cptObstacleArG = 0;

void obstacleArriereGauche(){
  //Serial.println("obstacle arriere gauche detecté");
  isObstacleArG++;
  if(cptObstacleArG > 1000){
    isObstacleArG = true;
  }
  //arret();
}

void obstacleArriereDroit(){
  //Serial.println("obstacle arriere droit detecté");
  isObstacleArD = true;
  //arret();
}

void NoObstacleArriereGauche(){
  isObstacleArG = 0;
  isObstacleArG = false;
}

void NoObstacleArriereDroit(){
  isObstacleArD = false;
}*/

// lien pour telemetres IR https://www.instructables.com/How-to-Use-the-Sharp-IR-Sensor-GP2Y0A41SK0F-Arduin/
// Telemetres_IR_AV droite et gauche
SharpIR telAvG(SharpIR::GP2Y0A21YK0F, A0);
SharpIR telAvD(SharpIR::GP2Y0A21YK0F, A1);
int Dist_AvG;
int Dist_AvD;

// Telemetres_IR_AR droite et gauche
SharpIR telArG(SharpIR::GP2Y0A21YK0F, A2);
SharpIR telArD(SharpIR::GP2Y0A21YK0F, A3);
int Dist_ArG;
int Dist_ArD;

//servo positionné sur la gauche du robot
Servo myservo;

int pin_servo = 6;       // Pin 6 sur lequel est branché le servo sur l'Arduino si vous utilisez un ESP32 remplacez le 6 par 4 et si vous utilisez un ESP8266 remplacez le 6 par 2
int position = 80;       // Position souhaitée
int angle_depart = 140; // vers l'avant du robot
int angle_final = 10;   // vers l'arrière du robot
int increment = 5;      // pas 

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
int vitesseENB = 80; // roue droite

void setup() {
  Serial.begin(9600);

  pinMode(pin_tirette, INPUT_PULLUP);
  MsTimer2::set(10000, finRun);
   
  myservo.attach(pin_servo);
  
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

  //attachInterrupt(digitalPinToInterrupt(18), obstacleArriereGauche, FALLING);
  //attachInterrupt(digitalPinToInterrupt(19), obstacleArriereDroit, FALLING);

  //attachInterrupt(digitalPinToInterrupt(24), NoObstacleArriereGauche, RISING);
  //attachInterrupt(digitalPinToInterrupt(20), NoObstacleArriereDroit, RISING);
}

void loop() {
  while(digitalRead(pin_tirette) && !isTimerSet);
  if(!isTimerSet){
    MsTimer2::start();
    isTimerSet = true;
  }
  Serial.println("Running OK");
  //Serial.println("Running");
  delay(500);



  
  //testServo();
  //testMoteurs();
  //testTelemetres();
  /*testMoteurs();
  testServo();
  delay(3000);

  if(!isObstacleArG){
    moveBackwardLeft();
    //Serial.println("dans le 1");
  }
  else{
    arretLeft();
    //Serial.println("dans le 2");
  }

  
  if(!isObstacleArD){
    moveBackwardRight();
    //Serial.println("dans le 3");
  }
  else{
    arretRight();
    //Serial.println("dans le 4");
  }
  */
 
}

void testServo(){
  myservo.write(position);
  
  for(int i=position; i<=angle_depart; i += increment){
    myservo.write(i);
    delay(200);
  }
}

void testMoteurs(){
  Forward();
  delay(2000);
  arret();
  delay(1000);
  Backward();
  delay(2000);
  arret();
  delay(1000);
}

void testTelemetres()
{
  Dist_AvG = telAvG.getDistance();
  Serial.print("Avant gauche : ");
  Serial.println(Dist_AvG);
  delay(1000);
  
  Dist_AvD = telAvD.getDistance();
  Serial.print("Avant droit : ");
  Serial.println(Dist_AvD);
  delay(1000);
  
  Dist_ArG = telArG.getDistance();
  Serial.print("Arriere gauche : ");
  Serial.println(Dist_ArG);
  delay(1000);
  
  Dist_ArD = telArD.getDistance();
  Serial.print("Arriere droit : ");
  Serial.println(Dist_ArD);
  delay(1000);

  Serial.println("");
}





// fonctions de mouvement

void arret()
{
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4, HIGH);
}

void arretLeft(){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
}

void arretRight(){
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}

void Forward()
{
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, LOW);
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

void moveBackwardLeft(){
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2, LOW);
        analogWrite(ENA,vitesseENA);
}

void moveBackwardRight(){
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
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

void finRun()
{
  Serial.println("fin du run");
  arret();
  while(1);
  
}
