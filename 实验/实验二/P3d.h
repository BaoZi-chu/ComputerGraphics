#pragma once
#include "P2d.h"
class CP3d : public CP2d
{
public:
	CP3d();
	virtual ~CP3d();
	CP3d(float, float, float);
	friend CP3d operator +(CP3d&, CP3d&);//���������
	friend CP3d operator -(CP3d&, CP3d&);
	friend CP3d operator *(CP3d&, float);
	friend CP3d operator *(float, CP3d&);
	friend CP3d operator /(CP3d&, float);
	friend CP3d operator+=(CP3d&, CP3d&);
	friend CP3d operator-=(CP3d&, CP3d&);
	friend CP3d operator*=(CP3d&, float);
	friend CP3d operator/=(CP3d&, float);
	float Mold();//����
public:
	float z;
};

