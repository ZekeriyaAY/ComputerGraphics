// GL1.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
// #include <tchar.h>
#include <GL/glut.h> // GLUT, includes glu.h and gl.

void init(void)
{
	glClearColor(0.9, 0.0, 0.1, 0.0); // set display window color to white
	glMatrixMode(GL_PROJECTION);	  // set projection parameters
	gluOrtho2D(0, 200, 0, 150);
}
void lineSegment(void)
{
	glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer

	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f, 1.0f, 1.0f); // set line segment color to green

	glVertex2i(20, 80);
	glVertex2i(165, 120);
	glVertex2i(100, 50);
	glVertex2i(35, 120);
	glVertex2i(180, 80);

	glEnd();

	glFlush(); // process all openGL routines as quickly as possible
}

int main(int argc, char *argv[])
{
	glutInit(&argc, (char **)argv);				 // Initialize GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
	glutInitWindowPosition(50, 100);			 // Position the window's initial top-left corner
	glutInitWindowSize(400, 300);				 // Set the window's initial width & height
	glutCreateWindow("OpenGL Yildiz Odev");		 // Create a window with the given title
	init();										 // Execute initialization procedure
	glutDisplayFunc(lineSegment);				 // Register display callback handler for window re-paint
	glutMainLoop();								 // Enter the infinitely event-processing loop
	return 0;
}
