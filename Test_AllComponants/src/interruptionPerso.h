//
// Created by gozlanp on 27/05/2021.
//

#ifndef TEST_ALLCOMPONANTS_INTERRUPTIONPERSO_H
#define TEST_ALLCOMPONANTS_INTERRUPTIONPERSO_H

bool tel53 = false;
bool tel52 = false;
bool tel51 = false;
bool tel50 = false;

ISR(PCINT0_vect){ // code qui s'execute lors d'une interruption
    // les if permettent de différencier le pin qui a lancé l'interruption

        if(digitalRead(53) == 0){ //(PINB & 1<<PORTB0) &&
            if(tel53 == false){
                Serial.println("je suis le pin 53");
                tel53 = true;
            }
        }
        if( digitalRead(52) == 0){
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
        }
}

#endif //TEST_ALLCOMPONANTS_INTERRUPTIONPERSO_H
