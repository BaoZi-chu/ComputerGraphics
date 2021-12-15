#pragma once
#include "RGB.h"

class CP2d
{
public:
	CP2d();
	virtual ~CP2d();
	CP2d(double, double);
	friend CP2d operator +(CP2d &, CP2d &);//‘ÀÀ„∑˚÷ÿ‘ÿ
	friend CP2d operator -(CP2d &, CP2d &);
	friend CP2d operator *(CP2d &, double);
	friend CP2d operator *(double, CP2d &);
	friend CP2d operator /(CP2d &, double);
public:
	double x, y;
	double w;
	CRGB   c;
};

