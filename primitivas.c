#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <stdio.h>
#include "primitivas.h"

/**Faz um truque envolendo operações bitwise onde você consegue pégar o código RGB 
   e convertê-lo para o esquema RGB do openGL.
**/
void pegar_cor(int RGB, GLfloat vetor_cor[3]){
		//pegar o R 
		vetor_cor[0] = (GLfloat) ((RGB & RGB_VERMELHO) >> 16);
		//pegar o G 
		vetor_cor[1] = (GLfloat) ((RGB & RGB_VERDE) >> 8);
		//pegar o B 
		vetor_cor[2] = (GLfloat) ((RGB & RGB_AZUL));

		//fazendo a normalização dos valores. 
		vetor_cor[0] = vetor_cor[0]/255;
		vetor_cor[1] = vetor_cor[1]/255;
		vetor_cor[2] = vetor_cor[2]/255;

		printf("RGB: %f %f %f\n", vetor_cor[0], vetor_cor[1], vetor_cor[2]);
}

//Desenhar as primitivas de OPENGL 
void desenhar_cuboide(int int_cor){
}

void desenhar_esfera(int int_cor){
	GLfloat cor[3];
	glPushMatrix();
	pegar_cor(int_cor, cor);
	
	//Preenchendo com a palheta RGB
	glColor3f(cor[0], cor[1], cor[2]);
	glTranslatef(0.0f, 1.5f, 0.0f);
	glutSolidSphere(0.3, 20, 20);
	glPopMatrix();

}

//Desenhar os membros do robô 
void desenhar_cabeca(){

}

//desenhando as partes dos braços
void desenhar_antebraco(GLfloat angulo){

}

void desenhar_braco(GLfloat angulo){

}

//desenhando as partes das pernas 
void desenhar_coxa(GLfloat angulo){

}

void desenhar_perna(GLfloat angulo){

}

//desenhando o torso 
void desenhar_torso(){

}

//por fim, protótipo para desenhar o humanoide em sua inteiridade:
void desenhar_humanoide(){

}

