#include "animacao.h"
#include <stdio.h>

float modulo(float numero){
    if (numero < 0){
        return numero * -1.0f;
    }

    return numero;
}

float sinal(float numero){
    if (numero < 0){
        return -1.0f;
    } 
    return 1.0f;
}

void idle(Corpo * boneco, int * caminhando){
    //definindo os parâmetros do boneco:
	//antebraço direito 
	boneco->antebraco_direito.angulo = 0.0f;
	boneco->antebraco_direito.x = 0.0f;
	boneco->antebraco_direito.y = 1.0f;
	boneco->antebraco_direito.z = 0.0f;
	

	//antebraço esquerdo
	boneco->antebraco_esquerdo.angulo =	0.0f;
	boneco->antebraco_esquerdo.x = 0.0f;
	boneco->antebraco_esquerdo.y = 1.0f;
	boneco->antebraco_esquerdo.z = 0.0f;

	//braco direito
	boneco->braco_direito.angulo = 0.0f;
	boneco->braco_direito.x = 0.0f;
	boneco->braco_direito.y = 1.0f;
	boneco->braco_direito.z = 0.0f;

	//braco esquerdo
	boneco->braco_esquerdo.angulo = 0.0f;
	boneco->braco_esquerdo.x = 0.0f;
	boneco->braco_esquerdo.y = 1.0f;
	boneco->braco_esquerdo.z = 0.0f;
	
	//coxa direita
	boneco->coxa_direita.angulo = 0.0f;
	boneco->coxa_direita.x = 0.0f;
	boneco->coxa_direita.y = 1.0f;
	boneco->coxa_direita.z = 0.0f;

	//coxa esquerda
	boneco->coxa_esquerda.angulo = 0.0f;
	boneco->coxa_esquerda.x = 0.0f;
	boneco->coxa_esquerda.y = 1.0f;
	boneco->coxa_esquerda.z = 0.0f;

	//perna direita
	boneco->perna_direita.angulo = 0.0f;
	boneco->perna_direita.x = 0.0f;
	boneco->perna_direita.y = 1.0f;
	boneco->perna_direita.z = 0.0f;

	//perna esquerda
	boneco->perna_esquerda.angulo = 0.0f;
	boneco->perna_esquerda.x = 0.0f;
	boneco->perna_esquerda.y = 1.0f;
	boneco->perna_esquerda.z = 0.0f;	
}

void caminhar(Corpo * boneco, int * caminhando, float * velocidade_caminhada){
    //Se a variável de caminhada for falsa, não faça nada.
    if (*caminhando == FALSE){
        //Ajustar a posição do boneco:
        idle(boneco, caminhando);
        return;    
    }
    
    
    //mover perna direita 
    boneco->coxa_direita.angulo += *velocidade_caminhada; 
    boneco->coxa_direita.x = 1.0;
    boneco->coxa_direita.y = 0.0;
    boneco->coxa_direita.z = 0.0;
    
    boneco->perna_direita.angulo += *velocidade_caminhada;
    boneco->perna_direita.x = 1.0;
    boneco->perna_direita.y = 0.0;
    boneco->perna_direita.z = 0.0;
    
    printf("%f\n", modulo(boneco->coxa_direita.angulo));

    if (modulo(boneco->coxa_direita.angulo) > 90 || modulo(boneco->perna_direita.angulo) > 90){        
        boneco->coxa_direita.angulo = 80 * sinal(boneco->coxa_direita.angulo);
        boneco->perna_direita.angulo = 80 * sinal(boneco->perna_direita.angulo);
        *velocidade_caminhada *= -1.0f;
    }

}