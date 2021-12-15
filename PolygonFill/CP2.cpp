#include "pch.h"
#include "CP2.h"

CP2::CP2(void)
{
	w = 1;
}


CP2::~CP2(void)
{
}
CP2::CP2(double x, double y)
{
	this->x = x;
	this->y = y;
	this->w = 1;
	this->c = CRGB(1.0, 1.0, 1.0);
}

CP2::CP2(double x, double y, CRGB c)
{
	this->x = x;
	this->y = y;
	this->w = 1.0;
	this->c = c;
}

CP2 operator +(const CP2& p1, const CP2& p2)
{
	CP2 p;
	p.x = p1.x + p2.x;
	p.y = p1.y + p2.y;
	return p;
}

CP2 operator *(const CP2& p1, double k)//��ͳ����Ļ�
{
	CP2 p;
	p.x = p1.x * k;
	p.y = p1.y * k;
	return p;
}

CP2 operator *(double k, const CP2& p1)//��ͳ����Ļ�
{
	CP2 p;
	p.x = k * p1.x;
	p.y = k * p1.y;
	return p;
}

CP2 operator += (CP2& p1, CP2& p2)
{
	p1.x += p2.x;
	p1.y += p2.y;
	return p1;
}


CP2 operator-=(const CP2& p1, const CP2& p2)
{
	CP2 p;
	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	return p;
}

CP2 operator*=(const CP2& p1, double k)
{
	CP2 p;
	p.x = p1.x * k;
	p.y = p1.y * k;
	return p;
}

CP2 operator/=(const CP2& p1, double k)
{
	if (fabs(k) < 1e-6)
		k = 1.0;
	CP2 p;
	p.x = p1.x / k;
	p.y = p1.y / k;
	return p;
}

CP2 operator -(const CP2& p1, const CP2& p2)
{
	CP2 p;
	p.x = p1.x - p2.x;
	p.y = p1.y - p2.y;
	return p;
}

CP2 operator /(const CP2& p1, double k)//��ͳ����ĳ�
{
	if (fabs(k) < 1e-6)
		k = 1.0;
	CP2 p;
	p.x = p1.x / k;
	p.y = p1.y / k;
	return p;
}