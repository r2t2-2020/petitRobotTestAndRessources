
int ArG; // 0 quand leds allumées == obstacle détecté
int ArD;
int pin_ArG = 4;
int pin_ArD = 5;

void setup() {
  Serial.begin(9600);
  
  pinMode(pin_ArG, INPUT);
  pinMode(pin_ArD, INPUT);

  attachInterrupt(digitalPinToInterrupt(21), obstacleArriereGauche, FALLING);
  attachInterrupt(digitalPinToInterrupt(20), obstacleArriereDroit, FALLING);
}
void obstacleArriereGauche(){
  Serial.println("obstacle arriere gauche detecté");
  
  //arret();
}

void obstacleArriereDroit(){
  Serial.println("obstacle arriere droit detecté");
  
  //arret();
}

void loop() {
  ArG = digitalRead(pin_ArG);
  ArD = digitalRead(pin_ArD);
  
  Serial.print("Gauche : ");
  Serial.println(ArG);
  
  Serial.println("");
  
  Serial.print("Droite : ");
  Serial.println(ArD);
  
  delay(1000);
}
