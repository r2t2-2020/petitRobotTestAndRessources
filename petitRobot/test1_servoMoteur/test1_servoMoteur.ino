#include <Servo.h>

/* Variables servo */
Servo myservo;
int pin_servo = 6; 
int position = 90;       
int angle_depart = 170; //max 180 
int angle_final = 10; // min 0
int increment = 5; 
/**/

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
/**/

void setup() {
  Serial.begin(115200);
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
  
  //myservo.write(angle_depart);
  myservo.write(position);
  delay(3000);

  for(int pos = position; pos<=angle_depart; pos += increment){
    myservo.write(pos); 

    Serial.println(myservo.read());
    delay(500);
  }

  /*for(int pos = angle_depart; pos>=position; pos -= increment){
    myservo.write(pos); 

    Serial.println(myservo.read());
    delay(500);
  }*/

  myservo.write(angle_final); 
  delay(1000);
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
