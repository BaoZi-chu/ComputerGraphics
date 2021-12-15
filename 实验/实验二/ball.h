#pragma once
#ifndef BALL_H
#define BALL_H
#include"triface.h"
class ball
{
public:
	GLuint Radius;
	GLuint Count;
	void DrawGeometry();
	
	
	ball(float radius=5) {
		t = 0;
		Radius = radius;
		Count = 4;
		n = int(8 * pow(4, Count));
		tri = new triface [n];
		GetGeometry();
	}
	void setRadius(float radius) {
		Radius = radius;
		n = int(8 * pow(4, Count));
		GetGeometry();
	}
	~ball() {

		delete[]tri;
		tri = nullptr;
			
	}
private:
	int n;//ÃæÆ¬¸öÊý
	triface* tri;
	GLuint Pattern;
	int t;
	void GetGeometry();
	void NormalTriangle(float* v1, float* v2, float* v3, float* vout);
	void Normalize(float* v, float radius);
	void GetTriangle(float* v1, float* v2, float* v3);
	void SubDivide(float* v1, float* v2, float* v3, int count);
	void Lookpos(float* v1, float* pos);
	

};
#endif

