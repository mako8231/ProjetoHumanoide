#ifndef ANIMACAO_H 
#define ANIMACAO_H

typedef struct corpo {
    //Angulos dos antebracos 
    float angulo_antebraco_direito;
    float angulo_antebraco_esquerdo;
    
    //Angulo dos braços 
    float angulo_braco_direito;
    float angulo_braco_esquerdo;

    //Angulo da coxa
    float angulo_coxa_direita;
    float angulo_coxa_esquerda;

    //Angulo da perna
    float angulo_perna_direita;
    float angulo_perna_esquerda;
    
} Corpo;

void mover_braco(float angulo, Corpo * boneco);


#endif