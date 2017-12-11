#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <time.h>
#include "BallsBox.h"

#ifndef point
#define point pair<double, double>
#define points vector<point>
#endif
#define BALLS_NUMBER 10
#define ORTO 25
#define TRIANGLE_AMOUNT 20
#define TIME 0.001

vector<Ball> BALLS;
BallsBox BALLSBOX;
void drawBalls();

using namespace std;

void display(void);
void reshape(int, int);
void onEF();
points inputCenters;
points inputSpeeds;
vector<double> inputRadiuses;
vector<double> inputMasses;

int main(int argc, char **argv)
{
	
	srand(time(NULL));

	for (int i = 0; i < BALLS_NUMBER; i++)
	{
		inputCenters.push_back(point((BOX - 1) * ((double)rand() / (double)RAND_MAX - (double)rand() / (double)RAND_MAX), (BOX - 1)  * ((double)rand() / (double)RAND_MAX - (double)rand() / (double)RAND_MAX)));
		inputSpeeds.push_back(point((BOX - 1) * ((double)rand() / (double)RAND_MAX - (double)rand() / (double)RAND_MAX), (BOX - 1)  * ((double)rand() / (double)RAND_MAX - (double)rand() / (double)RAND_MAX)));
		inputRadiuses.push_back((double)rand() / (double)RAND_MAX);
		inputMasses.push_back((double)rand() / (double)RAND_MAX);
	}

		BALLSBOX.init(inputCenters, inputSpeeds, inputRadiuses, inputMasses, TIME);

	glutInit(&argc, argv); // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE); // Set up a basic display buffer (only single buffered for now)
	glutInitWindowSize(600, 600); // Set the width and height of the window
	glutInitWindowPosition(750, 100); // Set the position of the window
	glutCreateWindow("Your first OpenGL Window"); // Set the title for the window
												  /*bst.updateDiagram();*/


	glutIdleFunc(onEF);
	glutDisplayFunc(display); // Tell GLUT to use the method "display" for rendering
	glutReshapeFunc(reshape); // Tell GLUT to use the method "reshape" for reshaping
	glutMainLoop(); // Enter GLUT's main loop




	system("pause");
	return 0;
}


void drawBalls()
{

	glClear(GL_COLOR_BUFFER_BIT);//Clear the screen
	glClearColor(1.0f, 0.6f, 0.2f, 1.0f);
	GLfloat twicePi = 2.0f * M_PI;
	for (int j = 0; j < BALLS.size(); j++)
	{
		glColor3f(BALLS[j].getMass(), 0., 0.);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2f(BALLS[j].center.first, BALLS[j].center.second); // center of circle
		for (int i = 0; i <= TRIANGLE_AMOUNT; i++) 
		{

			glVertex2f(
				BALLS[j].center.first + (BALLS[j].getRadius() * cos(i *  twicePi / TRIANGLE_AMOUNT)),
				BALLS[j].center.second + (BALLS[j].getRadius() * sin(i * twicePi / TRIANGLE_AMOUNT))
			);
		}
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i <= TRIANGLE_AMOUNT; i++) {
			glVertex2f(
				BALLS[j].center.first + (BALLS[j].getRadius() * cos(i *  twicePi / TRIANGLE_AMOUNT)),
				BALLS[j].center.second + (BALLS[j].getRadius() * sin(i * twicePi / TRIANGLE_AMOUNT))
			);
		}
		glEnd();
	}

	// Draws BOX:
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(BOX, BOX);
	glVertex2f(-BOX, BOX);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(-BOX, BOX);
	glVertex2f(-BOX, -BOX);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(-BOX, -BOX);
	glVertex2f(BOX, -BOX);
	glEnd();
	glBegin(GL_LINES);
	glVertex2f(BOX, -BOX);
	glVertex2f(BOX, BOX);
	glEnd();
}

void onEF()
{
	//system("pause");
	BALLSBOX.timeStep();
	BALLS = BALLSBOX.getBalls();
	glutPostRedisplay();
}

void reshape(int width, int height)
{

	glViewport(0, 0, (GLsizei)width, (GLsizei)height); // Set our viewport to the size of our window
	glMatrixMode(GL_PROJECTION); // Switch to the projection matrix so that we can manipulate how our scene is viewed
	glLoadIdentity(); // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
					  ///gluPerspective(22.5, (GLfloat)width / (GLfloat)height, 1.0, 100.0); // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
	glOrtho(-ORTO, ORTO, -ORTO, ORTO, -1, 10);
	glMatrixMode(GL_MODELVIEW); // Switch back to the model view matrix, so that we can start drawing shapes correctly
}

void display(void)
{
	std::cout << "display\n";
	glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations
	glTranslatef(0.0f, 0.0f, -5.0f);

	drawBalls();
	glutSwapBuffers();
	glFlush();
}


