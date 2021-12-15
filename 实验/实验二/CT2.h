#pragma once
class CT2
{
public:
	CT2();
	virtual ~CT2();
	CT2(float u, float v);
	friend CT2 operator +(const CT2&, const CT2&);
	friend CT2 operator -(const CT2&, const CT2&);
	friend CT2 operator *(const CT2&, float);
	friend CT2 operator *(float, const CT2&);
	friend CT2 operator /(const CT2&, float);
	friend CT2 operator+=(CT2&, CT2&);
	friend CT2 operator-=(CT2&, CT2&);
	friend CT2 operator*=(CT2&, float);
	friend CT2 operator/=(CT2&, float);
public:
	float u;
	float v;
};

