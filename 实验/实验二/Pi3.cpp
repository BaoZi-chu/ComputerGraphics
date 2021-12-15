#include "pch.h"
#include "Pi3.h"

CPi3::CPi3()
{
	this->z = 0.0;
}

CPi3::~CPi3()
{
}

CPi3::CPi3(double x0, int y0, double z0) :CPi2(x0, y0)
{
	this->z = z0;
}