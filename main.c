#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#include "primitivas.h"

float angulo_braco_esquerdo = 0.0f; 
float angulo_braco_direito = 0.0f;

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.5, 7.0, 
			  0.0, 1.0, -1.0, 
			  0.0, 1.0, 0.0);

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
	const float velocidade_rotacao = 0.7;
	switch (key){
		case 'i':
			angulo_braco_direito += velocidade_rotacao;
			printf("Angulo: %f\n", angulo_braco_direito);
			break;
	}

	glutPostRedisplay();
}

int main(int argc, char ** argv){
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
