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

}

//Desenhar as primitivas de OPENGL:


//função que define a primitiva do cubo:
void primitiva_cubo(float pos_x, float pos_y, float pos_z, float escala_x, float escala_y, float escala_z, GLfloat angulo, GLfloat rot_x, GLfloat rot_y, GLfloat rot_z){
	glRotatef(angulo, rot_x, rot_y, rot_z);
	glTranslatef(pos_x, pos_y, pos_z);
	glScalef(escala_x, escala_y, escala_z);
	glutSolidCube(1.0);
}

void desenhar_cuboide(int int_cor, float pos_x, float pos_y, float pos_z, float escala_x, float escala_y, float escala_z, GLfloat angulo, GLfloat rot_x, GLfloat rot_y, GLfloat rot_z){
	GLfloat cor[3];
	
	pegar_cor(int_cor, cor);

	/**~~~~~~~~CRIANDO UM MODELO 3D COM LINHAS PRETAS PARA O CONTORNO DO MODELO~~~~~~**/

	glPushMatrix();
	
	//criando o outline wireframe:
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glColor3f(0, 0, 0);
	primitiva_cubo(pos_x, pos_y, pos_z, escala_x, escala_y, escala_z, angulo, rot_x, rot_y, rot_z);
	//desabilitando o modo wireframe
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	glPopMatrix();

	/**~~~~~~~~AQUI CRIA-SE UM MODELO DE COR SÓLIDA USANDO OS MESMOS PARÂMETROS~~~~~~**/

	glPushMatrix();

	glColor3f(cor[0], cor[1], cor[2]);
	
	//glTranslatef(0.0f, 0.7f, 0.0f);
	primitiva_cubo(pos_x, pos_y, pos_z, escala_x, escala_y, escala_z, angulo, rot_x, rot_y, rot_z);

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
void desenhar_antebraco(GLfloat angulo, float pos_x, float pos_y, float pos_z, float rot_x, float rot_y, float rot_z){
	//desenhar_cuboide(COR_DE_PELE, -0.8f, 0.7f, 0.0f, 0.3f, 1.0f, 0.5f);
	desenhar_cuboide(COR_DE_PELE, pos_x, pos_y, pos_z, 0.3f, 0.7f, 0.5f, angulo, pos_x, pos_y, pos_z);
}

void desenhar_braco(GLfloat angulo, float pos_x, float pos_y, float pos_z, float rot_x, float rot_y, float rot_z){
	desenhar_cuboide(COR_DE_PELE, pos_x, pos_y, pos_z, 0.3f, 0.7f, 0.5f, angulo, pos_x, pos_y, pos_z);	
}

//desenhando as partes das pernas 
void desenhar_coxa(GLfloat angulo, float pos_x, float pos_y, float pos_z, float rot_x, float rot_y, float rot_z){
	desenhar_cuboide(COR_DA_CALCA, pos_x, pos_y, pos_z, 0.5f, 0.7f, 0.5f, angulo, pos_x, pos_y, pos_z);
}

void desenhar_perna(GLfloat angulo, float pos_x, float pos_y, float pos_z, float rot_x, float rot_y, float rot_z){
	desenhar_cuboide(COR_DA_CALCA, pos_x, pos_y, pos_z, 0.5f, 0.7f, 0.5f, angulo, pos_x, pos_y, pos_z);	
}

//desenhando o torso 
void desenhar_torso(){
	desenhar_cuboide(COR_DA_CAMISA, 0.0f, 0.7f, 0.0f, 1.0f, 1.0, 1.0, 0.0, 0.0, 1.0, 0.0);
}

//por fim, protótipo para desenhar o humanoide em sua inteiridade:
void desenhar_humanoide(Corpo boneco){
//desenhando os componentes base do boneco
	desenhar_cabeca();
	desenhar_torso();
	//desenhando o antebraço esquerdo 
	desenhar_antebraco(boneco.antebraco_esquerdo.angulo, -0.8f, 0.7f, 0.0f, 
	boneco.antebraco_esquerdo.x, boneco.antebraco_esquerdo.y, boneco.antebraco_esquerdo.z);
	
	//desenhando o antebraço direito
	desenhar_antebraco(boneco.antebraco_direito.angulo, 0.8f, 0.7f, 0.0f,
	boneco.antebraco_direito.x, boneco.antebraco_direito.y, boneco.antebraco_direito.z);
	
	//desenhando o braço esquerdo
	desenhar_braco(boneco.braco_esquerdo.angulo, -0.8f, -0.2f, 0.0f,
	boneco.braco_esquerdo.x, boneco.braco_esquerdo.y, boneco.braco_esquerdo.z);
	
	//desenhando o braço direito
	desenhar_braco(boneco.braco_direito.angulo, 0.8f, -0.2f, 0.0f,
	boneco.braco_direito.x, boneco.braco_direito.y, boneco.braco_direito.z);
	
	//desenhando a coxa direita
	desenhar_coxa(boneco.coxa_direita.angulo, 0.3, -0.2, 0.0f,
	boneco.coxa_direita.x, boneco.coxa_direita.y, boneco.coxa_direita.z);
	
	//desenhando a coxa esquerda
	desenhar_coxa(boneco.coxa_esquerda.angulo, -0.3, -0.2, 0.0f,
	boneco.coxa_esquerda.x, boneco.coxa_esquerda.y, boneco.coxa_esquerda.z);
	
	//desenhando a perna esquerda
	desenhar_perna(boneco.perna_esquerda.angulo, -0.3, -1.0, 0.0f,
	boneco.perna_esquerda.x, boneco.perna_esquerda.y, boneco.perna_esquerda.z);
	
	//desenhando a perna direita
	desenhar_perna(boneco.perna_direita.angulo, 0.3, -1.0, 0.0f,
	boneco.perna_direita.x, boneco.perna_direita.y, boneco.perna_direita.z);
}

