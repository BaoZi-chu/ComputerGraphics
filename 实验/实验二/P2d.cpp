#include "pch.h"
#include "P2d.h"

CP2d::CP2d()
{
	this->x = 0;
	this->y = 0;
	this->w = 1.0;
}

CP2d::~CP2d()
{
}

CP2d::CP2d(double x, double y)
{
	this->x = x;
	this->y = y;
	this->w = 1.0;
}
CP2d operator +(CP2d &p1, CP2d &p2)//和
{
	CP2d p;
	p.x = p1.x + p2.x;
	p.y = p1.y + p2.y;
	return p;
}

CP2d operator -(CP2d &p1, CP2d &p2)//差
{
	CP2d p;
	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	return p;
}

CP2d operator *(CP2d &p, double k)//点和常量的积
{
	return CP2d(p.x*k, p.y*k);
}

CP2d operator *(double k, CP2d &p)//点和常量的积
{
	return CP2d(p.x*k, p.y*k);
}

CP2d operator /(CP2d &p, double k)//数除
{
	if (fabs(k) < 1e-6)
		k = 1.0;
	CP2d point;
	point.x = p.x / k;
	point.y = p.y / k;
	return point;
}
