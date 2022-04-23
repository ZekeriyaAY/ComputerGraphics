////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 2D bezier spline drawing example program.
// Written by Vladeta Stojanovic (0602920@live.abertay.ac.uk).
//
// Based on the Bezier curve rendering method described by Nils Pipenbrinck (http://www.cubic.org/docs/bezier.htm).
//
// Version: 241211 - Santa's elves have been extra busy with this piece of code ;)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include <windows.h>   // use as needed for your system
#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include "bcurve.h"
#include "timer.h"

using namespace std;

/////////////////////////////
//Global object variables
/////////////////////////////

//currently generated curves
BCurve *gBCurve0;
BCurve *gBCurve1;
BCurve *gBCurve2;

//the future curves that the current curves get lerped to
BCurve *gBCurve0t;
BCurve *gBCurve1t;
BCurve *gBCurve2t;

timer* gTimer;

/////////////////////////////
//Global program variables
/////////////////////////////
int gameWindow;
int _time;
int lastTime;
int delta;
bool futureCurvesReady;
bool presentCurvesReady;

//////////////////////////////////////
//Application function prototypes
//////////////////////////////////////
void SetupCurves()
{
	gBCurve0->points[4] = gBCurve1->points[1];
	gBCurve1->points[4] = gBCurve2->points[1];
	gBCurve2->points[4] = gBCurve0->points[1];
}

void SetupCurvesT()
{	
	gBCurve0t->points[4] = gBCurve1t->points[1];
	gBCurve1t->points[4] = gBCurve2t->points[1];
	gBCurve2t->points[4] = gBCurve0t->points[1];
}

inline float Lerp(float t, float a, float b)
{
	return (a + t * (b - a));
}

/////////////////////////////////
//GLUT/GL function prototypes
////////////////////////////////
void DrawScene();
void IdleScene();
void Visible(int vis);
void KeyboardInput(unsigned char cKey, int iX, int iY);
void DrawInfo();


int main(int argc, char **argv) 
{ 
	//FreeConsole(); //uncomment this to get console window back

	//////////////////////////////////////
	//Setup any global variables here
	//////////////////////////////////////
	gBCurve0 = new BCurve();
	gBCurve0->Init();

	gBCurve1 = new BCurve();
	gBCurve1->Init();

	gBCurve2 = new BCurve();
	gBCurve2->Init();

	gBCurve0t = new BCurve();
	gBCurve0t->Init();

	gBCurve1t = new BCurve();
	gBCurve1t->Init();

	gBCurve2t = new BCurve();
	gBCurve2t->Init();

	//setup scene timer
	gTimer = new timer();


	//////////////////////////
	// Setup OpenGL here
	//////////////////////////
    GLsizei iWidth = 720.0; 
    GLsizei iHeight = 540.0; 

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POINT_SMOOTH);

    glutInit(&argc, argv);
    glutInitWindowPosition( 0, 0);
    glutInitWindowSize(iWidth, iHeight);
    glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
    glutCreateWindow( "2D Bezier Curve" );
    glutDisplayFunc(DrawScene);
	glutVisibilityFunc(Visible);
    glutIdleFunc(IdleScene);
    glutKeyboardFunc(KeyboardInput);

    glutIgnoreKeyRepeat(1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 720.0, 0.0, 540.0);
	glMatrixMode(GL_MODELVIEW); 
	glPointSize(3.0);
	glClearColor (0.1, 0.57, 0.8, 1.0);
	gameWindow = glutGetWindow();

    glutMainLoop(); 
	return 0;
}



////////////////////////////
//Scene gets drawn here
////////////////////////////
void DrawScene()
{
	glClear(GL_COLOR_BUFFER_BIT); 

	DrawInfo();

	glLoadIdentity();

	gBCurve0->DrawCurve(1.0, 0, 0);
	gBCurve0->DrawCPoints();
	gBCurve1->DrawCurve(0, 1.0, 0);
	gBCurve1->DrawCPoints();
	gBCurve2->DrawCurve(0, 0.0, 1.0);
	gBCurve2->DrawCPoints();

	glutSwapBuffers(); 
}

void Visible(int vis)
{
	if(vis == GLUT_VISIBLE) 
	{
		glutIdleFunc(IdleScene);
	}
}

void KeyboardInput(unsigned char cKey, int iX, int iY)
{
	switch(cKey)
	{
	case ' ': //space key
		gBCurve0t->Init();
		gBCurve1t->Init();
		gBCurve2t->Init();
		SetupCurvesT();
		break;
	}
}


void DrawInfo()
{
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2i(5, 520);

	string s = "Example of infinite generation of 2D Bezier curves using De Casteljau's algorithm.";
	void * font = GLUT_BITMAP_HELVETICA_18;
	for (string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
	glPopMatrix();
}

