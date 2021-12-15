#pragma once
#include <gl/GL.h>
#ifndef TRIFACE_H
#define TRIFACE_H

class triface
{
public:
	triface() {
		for (int i = 0; i < 3; i++) {
			this->v1[i] = 0;
			this->v2[i] = 0;
			this->v3[i] = 0;
			this->pos[i][0] = 0;
			this->pos[i][1] = 0;
			this->normal[i] = 0;
		}
	}
	triface(float* v1, float* v2, float* v3,float pos[3][2],GLfloat normal[3]) {
		for (int i = 0; i < 3; i++) {
			this->v1[i] = v1[i];
			this->v2[i] = v2[i];
			this->v3[i] = v3[i];
			this->pos[i][0] = pos[i][0];
			this->pos[i][1] = pos[i][1];
			this->normal[i] = normal[i];
		}
	}
	float v1[3];
	float v2[3];
	float v3[3];
	float pos[3][2];
	GLfloat normal[3];
};
#endif 
