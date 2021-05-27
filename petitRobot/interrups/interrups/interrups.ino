

void setup() {
  Serial.begin(115200);

  pinMode(13, INPUT_PULLUP); //_PULLUP
  pinMode(53, INPUT_PULLUP);

  PCICR =1;
  //PCICR |= (1 << PCIE2);     //Set PCIE0 to enable PCMSK0 scan.
  //PCMSK2 |= B11000000;
  /*PCMSK2 |= (1 << PCINT7);  //Set PCINT0 (digital input 22) to trigger an interrupt on state change.
  PCMSK2 |= (1 << PCINT0);*/
  PCMSK0 = 0b10000001; // masque pour 0 et 7 eme bits, permet de les activer en interruption
 
  sei();
}
  bool gauche = false;
  bool droite = false;
  int cpt = 0;

  ISR(PCINT0_vect){ // code qui s'execute lors d'une interruption
  //les if permettent de différencier le pin qui a lancé l'interruption
    if(PINB & 1<<PORTB7){ //PINB = input register of port, 1<<PORTB7 = regarde 7eme bit
      //droite = true;
      cpt++;
    }
    if(PINB & 1<<PORTB0){
      //gauche = true;
      cpt--;
    }
    
    
  }
  

void loop() {
  Serial.println(cpt);
  delay(500);
  /*if(gauche == true){
    Serial.println("gauche true");
  }
  else{
    Serial.println("gauche false");
  }
  if(droite == true){
    Serial.println("droite true");
  }
  else{
    Serial.println("droite false");
  }
  delay(500);*/
}
