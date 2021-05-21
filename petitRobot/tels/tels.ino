
int valeur; // 0 quand leds allumées

void setup() {
  // put your setup code here, to run once:
  pinMode(3, INPUT);
  Serial.begin(9600);
}

void loop() {
  valeur = digitalRead(3);
  Serial.print("valeur : ");
  Serial.println(valeur);
  delay(100);
}
