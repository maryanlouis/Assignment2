#include "stdafx.h"
#include <GL/glut.h>
#include <GL/GL.h>
#include <math.h>

using namespace std;

void handleKeypress(unsigned char key, int x, int y) {

	switch (key) {

	case 27: //Escape key
		exit(0);
		break;
	
	}
}

void init(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);//Enable color
	glClearColor(0.1f, 0.1f, 0.3f, 1.0);  //Change the background 
}

void handleResize(int w, int h) {

	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);

}

float xaxis = 0.0f;		//to translate the square in x axis

float yaxis = 0.0f;		//to translate the square in y axis
float zaxis = 0.0f;
float angleR = 0.0f;   //to rotate the square  
float c = 0.0f;
//float a = 0.0f;	   // for scaling
float flag = 0.0f;

void circle(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);   //Switch to the drawing perspective
	glLoadIdentity();             //Reset the drawing perspective
	#define PI 3.14
	glPushMatrix();
	glTranslatef(-5.0f, 5.0f, -100.0f);  // move to new refrence point
	glTranslatef(xaxis, yaxis, 0.0f);
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i <= 360; i++)
		glVertex3f(sin(i*PI / 180) * 30, cos(i*PI / 180) * 30, 0);
	glEnd();
	glPopMatrix();
	if (flag == 0.0)

		if (xaxis < 10.0f)
			xaxis += 0.01f;
		else if (yaxis > -10.0f)
			yaxis -= 0.01f;
		else
			flag = 1.0;
	if (flag == 1.0)
		if (xaxis >= 0.0f)
			xaxis -= 0.01f;
		else if (yaxis <= 0.0f)
			yaxis += 0.01f;
		else
			flag = 0.0;

	float delta_theta = 0.01;
	float r = 10;
	
	glPushMatrix();

	glTranslatef(-5.0f, 5.0f, -100.0f);  // move to new refrence point
	
	glTranslatef(xaxis, yaxis, 0.0f);
	if (xaxis >= -10.0f || yaxis >= -10.0f) {
			glTranslatef(xaxis, 40.0f*yaxis, 0.0f);
	}
	glRotatef(angleR, xaxis, 1.0f, zaxis);
	
	glBegin(GL_POLYGON); // OR GL_LINE_LOOP
	for (float angle = 0; angle < 2 * PI; angle += delta_theta)
		glVertex3f(-20 + r * cos(angle), -20 + r * sin(angle), 0);

	glEnd();
	angleR += 0.1f;
	zaxis += 0.1f;

	glPopMatrix();

	glFlush();
	glutPostRedisplay();              //Tell GLUT that the display has changed

	glutTimerFunc(50, 0, 0);          //Tell GLUT to call update again in 25 milliseconds

	glutSwapBuffers();

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //sets the initial display mode
	glutInitWindowPosition(50, 100); //sets the initial window position
	glutInitWindowSize(1024, 764); //sets the initial window size
	glutCreateWindow("Circle"); // creates the window with name line
	init();
	glutDisplayFunc(circle); //sets the display callback for the current window.
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutMainLoop(); // enters the GLUT event processing loop
	return 0;
}