#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#include "primitivas.h"

//definindo constantes
#define PI 3.141592653589

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

float angulo_braco_esquerdo = 0.0f; 
float angulo_braco_direito = 0.0f;

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	float targetX = cam.x + sin(cam.yaw * PI/180.0f);
	float targetY = cam.y + sin(cam.pitch * PI/180.0f);
	float targetZ = cam.z - cos(cam.yaw * PI/180.0f);


	gluLookAt(cam.x, cam.y, cam.z, 	//posição da câmera (x, y, z) 
			  targetX, targetY, targetZ, 	//olhar para o alvo (x, y, z)
			  0.0, 1.0, 0.0);	//vetor de cima 	(x, y, z)

	//desenhando os componentes base do boneco
	desenhar_cabeca();
	desenhar_torso();
	//desenhando o antebraço esquerdo 
	desenhar_antebraco(0.0, -0.8f, 0.7f, 0.0f);
	//desenhando o antebraço direito
	desenhar_antebraco(0.0, 0.8f, 0.7f, 0.0f);
	//desenhando o braço esquerdo
	desenhar_braco(0.0, -0.8f, -0.2f, 0.0f);
	//desenhando o braço direito
	desenhar_braco(0.0, 0.8f, -0.2f, 0.0f);
	//desenhando a coxa direita
	desenhar_coxa(0.0, 0.3, -0.2, 0.0f);
	//desenhando a coxa esquerda
	desenhar_coxa(0.0, -0.3, -0.2, 0.0f);
	//desenhando a perna esquerda
	desenhar_perna(0.0, -0.3, -1.0, 0.0f);
	//desenhando a perna direita
	desenhar_perna(0.0, 0.3, -1.0, 0.0f);

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

	}

	glutPostRedisplay();
}

int main(int argc, char ** argv){
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
