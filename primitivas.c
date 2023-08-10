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
void desenhar_cuboide(int int_cor, float pos_x, float pos_y, float pos_z, float escala_x, float escala_y, float escala_z, GLfloat angulo){
	GLfloat cor[3];
	
	pegar_cor(int_cor, cor);

	glPushMatrix();
	
	glColor3f(cor[0], cor[1], cor[2]);
	
	//glTranslatef(0.0f, 0.7f, 0.0f);
	glRotatef(angulo, 1.0f, 0.0f, 0.0f);
	glTranslatef(pos_x, pos_y, pos_z);
	glScalef(escala_x, escala_y, escala_z);
	glutSolidCube(1.0);

	glPopMatrix();
}

void desenhar_esfera(int int_cor, float pos_x, float pos_y, float pos_z){
	GLfloat cor[3];
	glPushMatrix();
	
	pegar_cor(int_cor, cor);
	
	//Preenchendo com a palheta RGB
	glColor3f(cor[0], cor[1], cor[2]);
	glTranslatef(pos_x, pos_y, pos_z);
	//glTranslatef(0.0f, 1.5f, 0.0f);
	glutSolidSphere(0.3, 20, 20);
	
	glPopMatrix();

}

//Desenhar os membros do robô 
void desenhar_cabeca(){
	desenhar_esfera(COR_DE_PELE, 0.0f, 1.5f, 0.0f);
}

//desenhando as partes dos braços
void desenhar_antebraco(GLfloat angulo, float pos_x, float pos_y, float pos_z){
	//desenhar_cuboide(COR_DE_PELE, -0.8f, 0.7f, 0.0f, 0.3f, 1.0f, 0.5f);
	desenhar_cuboide(COR_DE_PELE, pos_x, pos_y, pos_z, 0.3f, 0.7f, 0.5f, angulo);
}

void desenhar_braco(GLfloat angulo, float pos_x, float pos_y, float pos_z){
	desenhar_cuboide(COR_DE_PELE, pos_x, pos_y, pos_z, 0.3f, 0.7f, 0.5f, angulo);	
}

//desenhando as partes das pernas 
void desenhar_coxa(GLfloat angulo, float pos_x, float pos_y, float pos_z){

}

void desenhar_perna(GLfloat angulo, float pos_x, float pos_y, float pos_z){

}

//desenhando o torso 
void desenhar_torso(){
	desenhar_cuboide(COR_DA_CAMISA, 0.0f, 0.7f, 0.0f, 1.0f, 1.0, 1.0, 0.0);
}

//por fim, protótipo para desenhar o humanoide em sua inteiridade:
void desenhar_humanoide(){

}

