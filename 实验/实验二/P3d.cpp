#include "pch.h"
#include "P3d.h"

CP3d::CP3d()
{
	this->z = 0.0;
}

CP3d::~CP3d()
{
}
CP3d::CP3d(float x0, float y0, float z0) :CP2d(x0, y0)
{
	this->z = z0;
}

CP3d operator +(CP3d& p1, CP3d& p2)//和
{
	CP3d p;
	p.x = p1.x + p2.x;
	p.y = p1.y + p2.y;
	p.z = p1.z + p2.z;
	return p;
}

CP3d operator -(CP3d& p1, CP3d& p2)//差
{
	CP3d p;
	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	p.z = p1.z - p2.z;
	return p;
}

CP3d operator *(CP3d& p, float k)//点和常量的积
{
	return CP3d(p.x * k, p.y * k, p.z * k);
}

CP3d operator *(float k, CP3d& p)//点和常量的积
{
	return CP3d(p.x * k, p.y * k, p.z * k);
}

CP3d operator /(CP3d& p, float k)//数除
{
	if (fabs(k) < 1e-6)
		k = 1.0;
	CP3d point;
	point.x = p.x / k;
	point.y = p.y / k;
	point.z = p.z / k;
	return point;
}

CP3d operator+=(CP3d& p1, CP3d& p2)
{
	p1.x = p1.x + p2.x;
	p1.y = p1.y + p2.y;
	p1.z = p1.z + p2.z;
	return p1;
}

CP3d operator-=(CP3d& p1, CP3d& p2)
{
	p1.x = p1.x - p2.x;
	p1.y = p1.y - p2.y;
	p1.z = p1.z - p2.z;
	return p1;
}

CP3d operator*=(CP3d& p1, float k)
{
	p1.x = p1.x * k;
	p1.y = p1.y * k;
	p1.z = p1.z * k;
	return p1;
}

CP3d operator/=(CP3d& p1, float k)
{
	if (fabs(k) < 1e-6)
		k = 1.0;
	p1.x = p1.x / k;
	p1.y = p1.y / k;
	p1.z = p1.z / k;
	return p1;
}

float CP3d::Mold()//长度
{
	float product = sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
	return product;
}