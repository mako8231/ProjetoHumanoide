#ifndef ANIMACAO_H 
#define ANIMACAO_H

typedef struct membro {
    float angulo;
    float x; 
    float y;
    float z; 
} Membro;

typedef struct corpo {
    //Angulos dos antebracos 
    Membro antebraco_direito;
    Membro antebraco_esquerdo;

    //Angulo dos braços 
    Membro braco_direito;
    Membro braco_esquerdo;

    //Angulo da coxa
    Membro coxa_direita;
    Membro coxa_esquerda;

    //Angulo da perna
    Membro perna_direita;
    Membro perna_esquerda;
    
} Corpo;


void mover_braco(float angulo, Corpo * boneco);


#endif