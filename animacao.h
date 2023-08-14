#ifndef ANIMACAO_H 
#define ANIMACAO_H

#define TRUE 1 
#define FALSE 0

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

//Estado inerte
void idle(Corpo * boneco, int * caminhando);

//Mover membro
void moverMembro(Membro * parte, float angulo, float x, float y, float z);

//Mover a perna direita 
void mover_perna_direita(Corpo * boneco, int * caminhando, float * velocidade_caminhada, float sinal);

//Mover a perna esquerda 
void mover_perna_esquerda(Corpo * boneco, int * caminhando, float * velocidade_caminhada, float sinal);

//Ciclo de caminhada
void caminhar(Corpo * boneco, int * caminhando, float * velocidade_caminhada);


#endif