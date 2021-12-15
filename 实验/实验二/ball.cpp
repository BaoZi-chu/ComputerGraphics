#include "pch.h"
#include "ball.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include <gl/GL.h>

void ball::NormalTriangle(float* v1, float* v2, float* v3, float* vout)
{
	//求三点构成的三角形面的法向量
	GLfloat v12[3], v23[3];
	for (int i = 0; i < 3; i++) {
		v12[i] = v2[i] - v1[i];
		v23[i] = v3[i] - v2[i];
	}

	vout[0] = v12[1] * v23[2] - v12[2] * v23[1];
	vout[1] = -(v12[0] * v23[2] - v12[2] * v23[0]);
	vout[2] = v12[0] * v23[1] - v12[1] * v23[0];
	Normalize(vout, 1);
}

void ball::Normalize(float* v, float radius)
{
	//向量的标准化,以模长为radius进行标准化
	GLfloat d = (GLfloat)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (d == 0.0) {
		return;
	}
	v[0] /= d; v[1] /= d; v[2] /= d;
	v[0] *= radius; v[1] *= radius; v[2] *= radius;
}
void ball::Lookpos(float* v1, float* pos)
{
	float r = sqrt(v1[0] * v1[0] + v1[2] * v1[2]);
	if (r != 0)
	{
		float t = v1[0] / r;
		float v = acos(t) * M_1_PI / 2;
		if (v1[2] < 0) {
			v =1 - v;
		}
		pos[0] = v;
	}
	else {
		pos[0] = 0.5;
	}//图片行坐标
	r = sqrt(v1[1] * v1[1] + v1[2] * v1[2]);
	if (r != 0)
	{
		float t = v1[1] / r;
		pos[1] = acos(t) * M_1_PI;
	}
	else {
		pos[1] = 0.5;
	}//图片列坐标


}

void ball::GetTriangle(float* v1, float* v2, float* v3)
{
	//以三点为顶点画三角形
	GLfloat normal[3] = { 0,0,0 };
	NormalTriangle(v1, v2, v3, normal);//求取面法向量
	
	float pos[3][2];
	Lookpos(v1, pos[0]);
	Lookpos(v2, pos[1]);
	Lookpos(v3, pos[2]);
	triface pp(v1, v2, v3, pos, normal);
	tri[t] = pp;
	t++;
}

void ball::SubDivide(float* v1, float* v2, float* v3, int count)
{
	//把count为级数，对一个三角形面的子划分
	if (0 >= count)	//count=0,则画由三点构成的三角形
	{
		GetTriangle(v1, v2, v3);
	}
	else
	{
		GLfloat v12[3], v23[3], v31[3];
		GLint i;
		for (i = 0; i < 3; i++) {
			v12[i] = (v1[i] + v2[i]) / 2;
			v23[i] = (v2[i] + v3[i]) / 2;
			v31[i] = (v3[i] + v1[i]) / 2;
		}
		Normalize(v12, (float)Radius);	//扩展模长
		Normalize(v23, (float)Radius);
		Normalize(v31, (float)Radius);

		SubDivide(v1, v12, v31, count - 1);
		SubDivide(v2, v23, v12, count - 1);
		SubDivide(v3, v31, v23, count - 1);
		SubDivide(v12, v23, v31, count - 1);
	}
}

void ball::DrawGeometry()
{
	for (int i = 0; i < n; i++) {
		glBegin(GL_TRIANGLES);
		glNormal3fv(tri[i].normal);
		glTexCoord2f(tri[i].pos[0][0], tri[i].pos[0][1]); glVertex3fv(tri[i].v1);
		glTexCoord2f(tri[i].pos[1][0], tri[i].pos[1][1]); glVertex3fv(tri[i].v2);
		glTexCoord2f(tri[i].pos[2][0], tri[i].pos[2][1]); glVertex3fv(tri[i].v3);
		glEnd();
	}																	
	

}

void ball::GetGeometry()
{
	t = 0;
	n = int(8 * pow(4, Count));
	//在此处获取球体的三角形面片
	GLfloat r = (GLfloat)Radius;
	GLfloat vdata[6][3] = {	//初始点坐标
		{r,0.0,0.0},{-r,0.0,0.0},
		{0.0,r,0.0},{0.0,-r,0.0},
		{0.0,0.0,r},{0.0,0.0,-r}
	};
	GLuint tindices[8][3] = {//初始面的构造
		{2,4,0},{2,0,5},{2,5,1},{2,1,4},
		{3,0,4},{3,5,0},{3,1,5},{3,4,1}
	};


	for (int i = 0; i < 8; i++) {
		SubDivide(&vdata[tindices[i][0]][0],
			&vdata[tindices[i][1]][0],
			&vdata[tindices[i][2]][0], Count);
	}
}

