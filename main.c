#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#include "primitivas.h"
#include "animacao.h"

//definindo constantes
#define PI 3.141592653589

/*~~~~~~~~~~~~~~~~ VARIÁVEIS DE CONTROLE DE ANIMAÇÃO ~~~~~~~~~~~~~~~~~~~~*/
int caminhando = FALSE; 


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

float angulo_braco_esquerdo = 0.0f; 
float angulo_braco_direito = 0.0f;
float velocidade_caminhada = 2.0f;

void display(){
	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	float targetX = cam.x + sin(cam.yaw * PI/180.0f);
	float targetY = cam.y + sin(cam.pitch * PI/180.0f);
	float targetZ = cam.z - cos(cam.yaw * PI/180.0f);


	gluLookAt(cam.x, cam.y, cam.z, 	//posição da câmera (x, y, z) 
			  targetX, targetY, targetZ, 	//olhar para o alvo (x, y, z)
			  0.0, 1.0, 0.0);	//vetor de cima 	(x, y, z)

	//função de desenhar humanoide
	desenhar_humanoide(boneco);
	//caminhar 
	caminhar(&boneco, &caminhando, &velocidade_caminhada);

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


		case '1':
			caminhando = TRUE;
			break;

	}

	glutPostRedisplay();
}

int main(int argc, char ** argv){
	
	printf("============== CONTROLES ============== \n");
	printf("W 		- 	FRENTE\n");
	printf("A 		- 	FRENTE\n");
	printf("S 		- 	FRENTE\n");
	printf("D 		-	FRENTE\n");
	printf("Q e E 		-   ROTAÇÃO DA CÂMERA\n");
	printf("============== CONTROLES ============== \n");
	
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

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Boneco Humanóide");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();	

	return 0;	
}
