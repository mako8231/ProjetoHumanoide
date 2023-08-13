#include "matematica.h"

//retorna o valor absoluto de um numero
float modulo(float numero){
    if (numero < 0){
        return numero * -1.0f;
    }

    return numero;
}

//Retorna um sinal de um número, se x>=0, retorna 1, caso contrário, -1
float sinal(float numero){
    if (numero < 0){
        return -1.0f;
    } 
    return 1.0f;
}
