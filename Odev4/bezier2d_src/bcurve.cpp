////////////////////////////////////////////////
// 2D Bezier curve interface implementation.
//
// Version: 231211
////////////////////////////////////////////////

#include "bcurve.h"
class BCurve
{
private:
	/* data */
public:
	BCurve(/* args */)
	{
		srand((unsigned)time(0));
	};
	~BCurve();

	void Init()
	{
		// generate random curve coords
		for (int i = 1; i < 5; ++i)
		{
			points[i].x = rand() % 700 + 50;
			points[i].y = rand() % 500 + 50;
		}
	}

	void ComputeBezier(GLfloatPoint &dest, const GLfloatPoint &a, const GLfloatPoint &b, const GLfloatPoint &c, const GLfloatPoint &d, const float t)
	{
		GLfloatPoint ab, bc, cd, abbc, bccd;
		Lerp(ab, a, b, t);
		Lerp(bc, b, c, t);
		Lerp(cd, c, d, t);
		Lerp(abbc, ab, bc, t);
		Lerp(bccd, bc, cd, t);
		Lerp(dest, abbc, bccd, t);
	}

	void DrawCPoints()
	{
		glColor3f(1.0, 0, 0);
		glPointSize(5.0);
		glBegin(GL_POINTS);
		for (int i = 1; i < 5; ++i)
		{
			glVertex2f(points[i].x, points[i].y);
		}
		glEnd();
	}

	void DrawCurve(float r, float g, float b)
	{

		glColor3f(r, g, b);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 1000; ++i)
		{
			float t = static_cast<float>(i) / 999.0f;

			ComputeBezier(points[0], points[1], points[2], points[3], points[4], t);
			glVertex2f(points[0].x, points[0].y);
		}
		glEnd();
	}
};
