#include "animacao.h"
#include <GL/freeglut.h>
#include <stdio.h>
#include "matematica.h"

void moverMembro(Membro * parte, float angulo, float x, float y, float z){
	parte->angulo = angulo;
	parte->x = x;
	parte->y = y;
	parte->z = z;
}

void idle(Corpo * boneco, int * caminhando){
    //definindo os parâmetros do boneco:
	//antebraço direito 
	*caminhando = FALSE;
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

void mover_perna_direita(Corpo * boneco, int * caminhando, float * velocidade_caminhada, float sign){
//mover perna direita 
    boneco->coxa_direita.angulo += *velocidade_caminhada * sign; 
    boneco->coxa_direita.x = 1.0;
    boneco->coxa_direita.y = 0.0;
    boneco->coxa_direita.z = 0.0;
    
    boneco->perna_direita.angulo += *velocidade_caminhada * sign;
    boneco->perna_direita.x = 1.0;
    boneco->perna_direita.y = 0.0;
    boneco->perna_direita.z = 0.0;

    if (modulo(boneco->coxa_direita.angulo) > 90 || modulo(boneco->perna_direita.angulo) > 90){        
        boneco->coxa_direita.angulo = 80 * sinal(boneco->coxa_direita.angulo);
        boneco->perna_direita.angulo = 80 * sinal(boneco->perna_direita.angulo);
        *velocidade_caminhada *= -1.0f;
    }
}

void mover_perna_esquerda(Corpo * boneco, int * caminhando, float * velocidade_caminhada, float sign){
//mover perna esquerda 
    boneco->coxa_esquerda.angulo += *velocidade_caminhada * sign; 
    boneco->coxa_esquerda.x = 1.0;
    boneco->coxa_esquerda.y = 0.0;
    boneco->coxa_esquerda.z = 0.0;
    
    boneco->perna_esquerda.angulo += *velocidade_caminhada * sign;
    boneco->perna_esquerda.x = 1.0;
    boneco->perna_esquerda.y = 0.0;
    boneco->perna_esquerda.z = 0.0;
    
    if (modulo(boneco->coxa_direita.angulo) > 90 || modulo(boneco->perna_direita.angulo) > 90){        
        boneco->coxa_esquerda.angulo = 80 * sinal(boneco->coxa_direita.angulo);
        boneco->perna_esquerda.angulo = 80 * sinal(boneco->perna_direita.angulo);
        *velocidade_caminhada *= -1.0f;
    }
}

void caminhar(Corpo * boneco, int * caminhando, float * velocidade_caminhada){
    mover_perna_direita(boneco, caminhando, velocidade_caminhada, -1.0f);
    mover_perna_esquerda(boneco, caminhando, velocidade_caminhada, 1.0f);
    glutPostRedisplay();
}