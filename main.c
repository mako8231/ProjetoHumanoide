/*
	**TRABALHO DE COMPUTAÇÃO GRÁFICA** 
		INTEGRANTES:
		-ARTHUR LIMA
		-LUCAS TAKASHI HONDA
		-MASAO MURAOKA NETO
*/


#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "primitivas.h"
#include "animacao.h"

//definindo constantes
#define PI 3.141592653589

//definindo variáveis da janela 
int w_width, w_height;


/*~~~~~~~~~~~~~~~~ VARIÁVEIS DE CONTROLE DE ANIMAÇÃO ~~~~~~~~~~~~~~~~~~~~*/
int caminhando = FALSE; 

/*~~~~~~~~~~~~~~~~ VARIÁVEIS DE CONTROLE DE MEMBRO ~~~~~~~~~~~~~~~~~~~~*/
//Vetor dos membros que indica a orientação do eixo na qual essa primitiva irá rotacionar.
float vetor_membro[3] = {0.0f, 1.0f, 0.0f};

/*~~~~~~~~~~~~~~~~ VARIÁVEIS DE CONTROLE DO MENU ~~~~~~~~~~~~~~~~~~~~*/
char membros_nome[4][30] = {
	"Perna direita\n",
	"Perna esquerda\n",
	"Braco direito\n",
	"Braco esquerdo\n"
};

int indice_membro = 0;

int menu_principal = TRUE;
int menu_membro = FALSE; 

//criando uma estrutura de dados para a camera:
typedef struct camera {
	float x;
	float y;
	float z; 
	float yaw;
	float pitch;
} Camera;

//Declarar a câmera
Camera cam;

//Declarar os parâmetros do boneco:
Corpo boneco;
float velocidade_caminhada = 4.0f;

Membro * boneco_membros[4][2];


void textoMenuPrincipal(){
	//Renderizar o texto:
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(0, 300);
	const char * cam_texto = "CONTROLES DA CAMERA:\nW - Frente\nA - Esquerda\nS - Atras\nD - Direita\nQ e E - Rotacionar a Camera\n";
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)cam_texto);

	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(500, 300);
	const char * control_texto = "CONTROLES DO PERSONAGEM:\n1 - Caminhar/Parar\n2 - Selecionar Membro";
	
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)control_texto);
}

void textoMenuMembro(){
	//Renderizar o texto de opções:
	glColor3f(0.0f, 0.3f, 1.0f);
	glRasterPos2f(0, 100);
	const char * membro_menu = "1 - Braco Esquerdo\n2 - Braco Direito\n3 - Perna Esquerda\n4 - Perna Direita\n";
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)membro_menu);

	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2f(500, 500);
	const char * sair = "R - Sair do menu de membro\n";
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)sair);


	//Renderizar o texto de opções do vetor:
	glColor3f(0.0f, 0.3f, 1.0f);
	glRasterPos2f(530, 350);
	const char * vetor_pos_menu = "ROTACAO:\nQ e E - Alterar Rotacao\nOPCOES DO VETOR:\n5-X do membro superior\n6-Y do membro superior\n7-Z do membro superior\n\nA-X do membro inferior\nS-Y do membro inferior\nD-Z do membro inferior\nZ-X Alterar rotacao do\n membro inferior";
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)vetor_pos_menu);


	//Renderizar o label de menu de membro:
	glColor3f(0.0f, 1.0f, 1.0f);
	glRasterPos2f(0, 500);
	const char * membro_texto = "MEMBRO SELECIONADO:\n";
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)membro_texto);

	//Renderizar o item do membro:
	glColor3f(0.0f, 1.0f, 1.0f);
	glRasterPos2f(0, 470);
	const char * membro = membros_nome[indice_membro];
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)membro);
	
	//Parâmetros do membro superior:
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(0, 400);
	char parametros[300];
	sprintf(parametros, "Angulo: %0.2f", boneco_membros[indice_membro][0]->angulo);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)parametros);
	

	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(0, 370);
	char vetor_eixo[800];
	sprintf(vetor_eixo, "Vetor de eixo de rotacao (%0.1f, %0.1f, %0.1f)", boneco_membros[indice_membro][0]->x, boneco_membros[indice_membro][0]->y, boneco_membros[indice_membro][0]->z);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)vetor_eixo);
	
	//Parâmetros do membro inferior:
	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(0, 320);
	char parametros_inf[300];
	sprintf(parametros_inf, "Angulo Inferior: %0.2f", boneco_membros[indice_membro][0]->angulo);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)parametros_inf);
	

	glColor3f(1.0f, 1.0f, 1.0f);
	glRasterPos2f(0, 300);
	char vetor_eixo_inf[800];
	sprintf(vetor_eixo_inf, "Vetor de eixo de rotacao (%0.1f, %0.1f, %0.1f)", boneco_membros[indice_membro][1]->x, boneco_membros[indice_membro][1]->y, boneco_membros[indice_membro][1]->z);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)vetor_eixo_inf);
	


}

void renderizarTexto(){
	//Mudar para a projeção ortográfica
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0, w_width, 0, w_height); //dimensões da janela

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	if (menu_principal){
		textoMenuPrincipal();
	} else if (menu_membro){
		textoMenuMembro();
	}

	glPopMatrix();

	// Restaurando a projeção para o sistema de referência da câmera
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);


}

void display(){
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	float targetX = cam.x + sin(cam.yaw * PI/180.0f);
	float targetY = cam.y + sin(cam.pitch * PI/180.0f);
	float targetZ = cam.z - cos(cam.yaw * PI/180.0f);


	gluLookAt(cam.x, 	cam.y, cam.z, 		//posição da câmera (x, y, z) 
			  targetX, targetY, targetZ, 	//olhar para o alvo (x, y, z)
			  0.0, 		1.0, 	0.0	   );	//vetor de cima 	(x, y, z)

	//função de desenhar humanoide
	desenhar_humanoide(boneco);
	//caminhar 
	if (caminhando == TRUE){
		caminhar(&boneco, &caminhando, &velocidade_caminhada);
	}

	//Renderizar o texto
	renderizarTexto();

	glutSwapBuffers();

}


void reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
	const float camera_spd = 0.1f; 
	const float rotation_spd = 2.0f;
	
	//CONTROLES DO MENU 1 
	if (menu_principal){	
		switch (key){
			/*CONTROLES DA CÂMERA: */
			case 'w':

				cam.x += camera_spd * sin(cam.yaw * PI / 180.0f);
				cam.z -= camera_spd * cos(cam.yaw * PI / 180.0f);

				break;
			case 'a':

				cam.x -= camera_spd * cos(cam.yaw * PI / 180.0f);
				cam.z -= camera_spd * sin(cam.yaw * PI / 180.0f);

				break;
			case 's':

				cam.x -= camera_spd * sin(cam.yaw * PI / 180.0f);
				cam.z += camera_spd * cos(cam.yaw * PI / 180.0f);

				break;
			case 'd':

				cam.x += camera_spd * cos(cam.yaw * PI / 180.0f);
				cam.z += camera_spd * sin(cam.yaw * PI / 180.0f);

				break;

			case 'q':
				cam.yaw += rotation_spd;
				break;	


			case 'e':
				cam.yaw -= rotation_spd;
				break;

			/*CONTROLES DAS ANIMAÇÕES DO BONECO*/

			//Ciclo de caminhada
			case '1':
				caminhando = !caminhando;
				break;
			
			case '2':
				menu_principal = FALSE; 
				menu_membro = TRUE;
				idle(&boneco, &caminhando);
				break;
			
			//Reiniciar animação para a posição original.
			case 'r':
				idle(&boneco, &caminhando);
				break;
			
		}
	} else if (menu_membro){
		switch (key) {
			case '1':
				indice_membro = 0;
			break;

			case '2':
				indice_membro = 1;
			break;

			case '3':
				indice_membro = 2;
			break;

			case '4':
				indice_membro = 3;
			break;

			case 'q':
				boneco_membros[indice_membro][0]->angulo += 1.0f;
				boneco_membros[indice_membro][1]->angulo += 1.0f;
			break;
			
			case 'e':
				boneco_membros[indice_membro][0]->angulo -= 1.0f;
				boneco_membros[indice_membro][1]->angulo -= 1.0f;
			break;

			case '5':
				if (boneco_membros[indice_membro][0]->x == 0.0f){
					
					boneco_membros[indice_membro][0]->x = 1.0f;
					boneco_membros[indice_membro][1]->x = 1.0f;
				} else {
					boneco_membros[indice_membro][0]->x = 0.0f;
					boneco_membros[indice_membro][1]->x = 0.0f;
				}
			break;

			
			case '6':
				if (boneco_membros[indice_membro][0]->y == 0.0f){
					
					boneco_membros[indice_membro][0]->y = 1.0f;
					boneco_membros[indice_membro][1]->y = 1.0f;
				} else {
					boneco_membros[indice_membro][0]->y = 0.0f;
					boneco_membros[indice_membro][1]->y = 0.0f;
				}
			break;
			
			case '7':
				if (boneco_membros[indice_membro][0]->z == 0.0f){
					
					boneco_membros[indice_membro][0]->z = 1.0f;
					boneco_membros[indice_membro][1]->z = 1.0f;
				} else {
					boneco_membros[indice_membro][0]->z = 0.0f;
					boneco_membros[indice_membro][1]->z = 0.0f;
				}
			break;

			case 'a':
				if (boneco_membros[indice_membro][1]->x == 0.0f){
					boneco_membros[indice_membro][1]->x = 1.0f;
				} else {
					boneco_membros[indice_membro][1]->x = 0.0f;
				}
			break;

			case 's':
				if (boneco_membros[indice_membro][1]->y == 0.0f){
					boneco_membros[indice_membro][1]->y = 1.0f;
				} else {
					boneco_membros[indice_membro][1]->y = 0.0f;
				}
			break;

			case 'd':
				if (boneco_membros[indice_membro][1]->z == 0.0f){
					boneco_membros[indice_membro][1]->z = 1.0f;
				} else {
					boneco_membros[indice_membro][1]->z = 0.0f;
				}
			break;

			case 'z':
				boneco_membros[indice_membro][1]->angulo += 1; 
			break;

			case 'x':
				boneco_membros[indice_membro][1]->angulo -= 1; 
			break;
			
			case 'r':
				menu_membro = FALSE; 
				menu_principal = TRUE;
				idle(&boneco, &caminhando);
			break;
		}
	}

	glutPostRedisplay();
}

int main(int argc, char ** argv){
	
	//definindo os valores
	w_width = 800;
	w_height = 600;

	//definindo os parâmetros do boneco:
	//antebraço direito 
	boneco.antebraco_direito.angulo = 0.0f;
	boneco.antebraco_direito.x = 0.0f;
	boneco.antebraco_direito.y = 1.0f;
	boneco.antebraco_direito.z = 0.0f;
	

	//antebraço esquerdo
	boneco.antebraco_esquerdo.angulo =	0.0f;
	boneco.antebraco_esquerdo.x = 0.0f;
	boneco.antebraco_esquerdo.y = 1.0f;
	boneco.antebraco_esquerdo.z = 0.0f;

	//braco direito
	boneco.braco_direito.angulo = 0.0f;
	boneco.braco_direito.x = 0.0f;
	boneco.braco_direito.y = 1.0f;
	boneco.braco_direito.z = 0.0f;

	//braco esquerdo
	boneco.braco_esquerdo.angulo = 0.0f;
	boneco.braco_esquerdo.x = 0.0f;
	boneco.braco_esquerdo.y = 1.0f;
	boneco.braco_esquerdo.z = 0.0f;
	
	//coxa direita
	boneco.coxa_direita.angulo = 0.0f;
	boneco.coxa_direita.x = 0.0f;
	boneco.coxa_direita.y = 1.0f;
	boneco.coxa_direita.z = 0.0f;

	//coxa esquerda
	boneco.coxa_esquerda.angulo = 0.0f;
	boneco.coxa_esquerda.x = 0.0f;
	boneco.coxa_esquerda.y = 1.0f;
	boneco.coxa_esquerda.z = 0.0f;

	//perna direita
	boneco.perna_direita.angulo = 0.0f;
	boneco.perna_direita.x = 0.0f;
	boneco.perna_direita.y = 1.0f;
	boneco.perna_direita.z = 0.0f;

	//perna esquerda
	boneco.perna_esquerda.angulo = 0.0f;
	boneco.perna_esquerda.x = 0.0f;
	boneco.perna_esquerda.y = 1.0f;
	boneco.perna_esquerda.z = 0.0f;	

	//definindo os parâmetros da câmera:
	cam.x = 0.0f;
	cam.y = 0.5f;
	cam.z = 7.0f;
	cam.yaw = 0.0;
	cam.pitch = 0.0;

	//passando os membros do corpo
	boneco_membros[0][0] = &boneco.coxa_direita;
	boneco_membros[0][1] = &boneco.perna_direita;

	boneco_membros[1][0] = &boneco.coxa_esquerda;
	boneco_membros[1][1] = &boneco.perna_esquerda;

	boneco_membros[2][0] = &boneco.antebraco_direito;
	boneco_membros[2][1] = &boneco.braco_direito;

	boneco_membros[3][0] = &boneco.antebraco_esquerdo;
	boneco_membros[3][1] = &boneco.braco_esquerdo;
	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(w_width, w_height);
	glutCreateWindow("Boneco Humanóide");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();	

	return 0;	
}
