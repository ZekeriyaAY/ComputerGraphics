## ***031990037 Zekeriya AY - Bilgisayar Grafikleri Ödev 4***

NOT: Uğraşmama rağmen ödevi yapamadım. Yapabildiğim kadarını eklemek istedim.

```makefile
# Makefile

build:
	g++ 3d_bezier_curves.cpp -o 3d_bezier_curves -lglut -lGLU -lGL
	./3d_bezier_curves
```

```cpp
// 3d_bezier_curves.cpp

#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
// #include <GLFW/glfw3.h>

using namespace std;

GLfloat ctrlpoints[4][3] = {
    {-2.0, 4.0, 3.0}, {4.0, -3.0, 2.0}, {-4.0, -2.0, 0.0}, {2.0, 2.0, -2.0}};

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);
}

void display(void) {
    gluLookAt(0.0, 0.0, -4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i <= 30; i++)
        glEvalCoord1f((GLfloat)i / 30.0);
    glEnd();

    glPointSize(12.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POINTS);
    for (int i = 0; i < 4; i++)
        glVertex3fv(&ctrlpoints[i][0]);
    glEnd();
    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        glOrtho(-5.0, 5.0, -5.0 * (GLfloat)h / (GLfloat)w,
                5.0 * (GLfloat)h / (GLfloat)w, -5.0, 5.0);
    else
        glOrtho(-5.0 * (GLfloat)w / (GLfloat)h,
                5.0 * (GLfloat)w / (GLfloat)h, -5.0, 5.0, -5.0, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void processNormalKeys(unsigned char key, int x, int y) {
    if (key == 27) // ESC = exit
        exit(0);
    else if (key == 'R')
    {
        glRotatef(5.0, 1.0, 1.0, 1.0);
        display();
    }
    else if (key == 'r')
    {
        cout << (float)((rand() % 11) - 5) << endl;
        fill(*ctrlpoints, *ctrlpoints + 4 * 3, ((rand() % 11) - 5));
        display();
    }
}

int main(int argc, char **argv) {
    srand(time(0));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    // glutIdleFunc(display);
    glutKeyboardFunc(processNormalKeys);
    glutMainLoop();
    return 0;
}
```
