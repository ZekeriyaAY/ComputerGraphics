#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

GLsizei windowWidth = 500, windowHeight = 500;
// GLfloat dataList[13] = {10.4,7.2,6.5,5.0,4.5,4.0,3.9,3.9,3.3,3.3,3.2,3.0,2.7};
GLfloat dataList[4] = {10.4,7.2,6.5,5.0};
GLfloat dataSum = 29.1;
GLint dataCount = 4;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, (GLdouble)windowWidth, 0, (GLdouble)windowHeight);
}

void cubukGrafik(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_LINES);
    glRecti(0.5f, 0.2f, -0.5f, -0.2f);
    glEnd();

    glFlush();
}

int main(int argc, char const *argv[]) {
    glutInit(&argc, (char **)argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(1280/2, 720/2);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Odev2-Cubuk Grafigi");
    init();
    glutDisplayFunc(cubukGrafik);
    glutMainLoop();

    return 0;
}
