#include <Servo.h>
#include <SharpIR.h>

/*
orange 0
jaune 1
vert 2
bleu 3

*/
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
  Serial.begin(115200);
  
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
}

void loop() {
  testTelemetres();
  testMoteurs();
  testServo();
  delay(3000);
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

void Forward()
{
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
