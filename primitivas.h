#ifndef PRIMITIVAS_H
	#define PRIMITIVAS_H
	
	#define RGB_VERMELHO 0xff0000
	#define RGB_AZUL  	 0x0000ff
	#define RGB_VERDE 	 0x00ff00

	//incluindo as bibliotecas OPENGL
	#include <GL/freeglut.h>
	#include <GL/glu.h>
	#include <GL/gl.h>
	
	void pegar_cor(int RGB, GLfloat vetor_cor[3]);

	//Desenhar as primitivas de OPENGL 
	void desenhar_cuboide(int int_cor, float pos_x, float pos_y, float pos_z, float escala_x, float escala_y, float escala_z);
	void desenhar_esfera(int int_cor, float pos_x, float pos_y, float pos_z);

	//Desenhar os membros do robô 
	void desenhar_cabeca();

	//desenhando as partes dos braços
	void desenhar_antebraco(GLfloat angulo);
	void desenhar_braco(GLfloat angulo);

	//desenhando as partes das pernas 
	void desenhar_coxa(GLfloat angulo);
	void desenhar_perna(GLfloat angulo);

	//desenhando o torso 
	void desenhar_torso();

	//por fim, protótipo para desenhar o humanoide em sua inteiridade:
	void desenhar_humanoide();

#endif 