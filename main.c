#include <GL/freeglut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include "primitivas.h"

#define COR_DE_PELE 0xeab676
#define COR_DA_CAMISA 0xff0000

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 3.0, 6.0, 
			  0.0, 1.0, 0.0, 
			  0.0, 1.0, 0.0);

	desenhar_esfera(COR_DE_PELE, 0.0f, 1.5f, 0.0f);
	desenhar_cuboide(COR_DA_CAMISA, 0.0f, 0.7f, 0.0f, 1.0f, 1.0, 1.0);


	glutSwapBuffers();

}

void reshape(int width, int height){
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char k, int x, int y){

}

int main(int argc, char ** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutKeyboardFunc(keyboard);
	glutCreateWindow("Boneco Humanóide");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();	

	return 0;	
}
