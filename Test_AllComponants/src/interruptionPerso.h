//
// Created by gozlanp on 27/05/2021.
//

#ifndef TEST_ALLCOMPONANTS_INTERRUPTIONPERSO_H
#define TEST_ALLCOMPONANTS_INTERRUPTIONPERSO_H

ISR(PCINT0_vect){ // code qui s'execute lors d'une interruption
    // les if permettent de différencier le pin qui a lancé l'interruption

        if(PINB & 1<<PORTB7){ //PINB = input register of port, 1<<PORTB7 = regarde 7eme bit
            //?
        }
        if(PINB & 1<<PORTB0){
            //?
        }
}

#endif //TEST_ALLCOMPONANTS_INTERRUPTIONPERSO_H
