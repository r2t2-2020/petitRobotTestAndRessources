/* Carte Driver ..*/
/* Moteur Droite*/
const byte ENA=10;// PWM
const byte IN1=8;// Dir   1A
const byte IN2=9; // 2A

/* Moteur Gauche*/
const byte ENB=13;// PWM
const byte IN4=12;// Dir  1B
const byte IN3=11; // 2B

int vitesseENA = 80;
int vitesseENB = 100;

void setup() {
  // put your setup code here, to run once:
  
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
  Turn_left();
  delay(1000);
  
  arret();
  delay(500);
  
  Backward();
  delay(1000);

  arret();
  delay(3000);
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
