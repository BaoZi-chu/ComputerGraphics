#include "pch.h"
#include "Pi2.h"

CPi2::CPi2()
{
	this->x = 0.0;
	this->y = 0;
	this->c = CRGB(1.0, 1.0, 1.0);
}

CPi2::~CPi2()
{
}

CPi2::CPi2(double x0, int y0)
{
	this->x = x0;
	this->y = y0;
}