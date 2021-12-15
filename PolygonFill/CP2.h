#pragma once
#include "CRGB.h"
class CP2
{
public:
	CP2(void);
	~CP2(void);
	CP2(double, double);
	CP2(double x, double y, CRGB c);
	friend CP2 operator +(const CP2&, const CP2&);
	friend CP2 operator -(const CP2&, const CP2&);
	friend CP2 operator *(const CP2&, double);
	friend CP2 operator *(double, const CP2&);
	friend CP2 operator /(const CP2&, double);
	friend CP2 operator+=(CP2&, CP2&);
	friend CP2 operator-=(CP2&, CP2&);
	friend CP2 operator*=(CP2&, double);
	friend CP2 operator/=(CP2&, double);
public:
	double x;
	double y;
	CRGB c;
	double w;
};

