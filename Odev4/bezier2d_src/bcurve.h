///////////////////////////////////////
// 2D Bezier curve interface.
// 
// Version: 231211
///////////////////////////////////////

#ifndef _BCURVE_H_
#define _BCURVE_H_

#include <GL/glut.h>
#include <cstdlib>
#include <ctime> 
#include <math.h>

struct GLfloatPoint
{ 
	GLfloat x,y;
};

class BCurve
{
public:

	//class constructor
	BCurve();

	//class destructor
	~BCurve();

	////////////////////////////////
	//Curve generation functions
	////////////////////////////////
	inline void Lerp(GLfloatPoint& dest, const GLfloatPoint& a, const GLfloatPoint& b, const float t)
	{
		 dest.x = a.x + (b.x-a.x)*t;
		 dest.y = a.y + (b.y-a.y)*t;
	}

	void Init(); //generate point coords here
	void ComputeBezier(GLfloatPoint& point,const GLfloatPoint& a, const GLfloatPoint& b, const GLfloatPoint& c, const GLfloatPoint& d, const float t);
	void DrawCPoints(); //draw the control points
	void DrawCurve(float r, float g, float b); 

public:
	GLfloatPoint points[4];
};

extern BCurve *gBCurve;

#endif