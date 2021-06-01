

void setup() {
  Serial.begin(115200);
  
  /*pinMode(50, INPUT_PULLUP);
  pinMode(51, INPUT_PULLUP);
  pinMode(52, INPUT_PULLUP);*/
  pinMode(53, INPUT_PULLUP);

  PCICR =1;
  PCMSK0 = 0b00000001; // masque pour 0 et 7 eme bits, permet de les activer en interruption
  //PCICR |= (1 << PCIE2);     //Set PCIE0 to enable PCMSK0 scan.
  //PCMSK2 |= B11000000;
  /*PCMSK2 |= (1 << PCINT7);  //Set PCINT0 (digital input 22) to trigger an interrupt on state change.
  PCMSK2 |= (1 << PCINT0);*/
  
  sei();
}
  bool gauche = false;
  bool droite = false;
  int cpt = 0;

  /*ISR(PCINT0_vect){ // code qui s'execute lors d'une interruption
  //les if permettent de différencier le pin qui a lancé l'interruption
    if((PINB & 1<<PORTB0) && digitalRead(53) == 0){ //PINB = input register of port, 1<<PORTB7 = regarde 7eme bit
      //droite = true;
      //Serial.println("blanc");
      if(droite == false){
        Serial.println("violet");
        cpt++;
        droite = true;
      }
    }
    if((PINB & 1<<PORTB7) && digitalRead(13) == 0){
      //Serial.println("orange");
      if(gauche == false){
        Serial.println("gris");
        cpt--;
        gauche = true;
      }
    }
  }*/

  bool tel53 = false;
  bool tel52 = false;
  bool tel51 = false;
  bool tel50 = false;
  
  ISR(PCINT0_vect){
    if(digitalRead(53) == 0){ //(PINB & 1<<PORTB0) && 
      if(tel53 == false){
        Serial.println("je suis le pin 53");
        tel53 = true;
      }
    }
    /*if( digitalRead(52) == 0){
      if(tel52 == false){
        Serial.println("je suis le pin 52");
        tel52 = true;
      }
    }
    if(digitalRead(51) == 0){
      if(tel51 == false){
        Serial.println("je suis le pin 51");
        tel51 = true;
      }
    }
    if(digitalRead(50) == 0){
      if(tel50 == false){
        Serial.println("je suis le pin 50");
        tel50 = true;
      }
    }*/
  }

void loop() {
  

}
