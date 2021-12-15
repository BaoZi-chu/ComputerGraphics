#pragma once
class CRGB
{
public:
	CRGB();
	CRGB(double, double, double);
	virtual ~CRGB();
	friend CRGB operator+(CRGB &, CRGB &);//运算符重载
	friend CRGB operator-(CRGB &, CRGB &);
	friend CRGB operator*(CRGB &, CRGB &);
	friend CRGB operator*(CRGB &, double);
	friend CRGB operator*(double, CRGB &);
	friend CRGB operator/(CRGB &, double);
	friend CRGB operator+=(CRGB &, CRGB &);
	friend CRGB operator-=(CRGB &, CRGB &);
	friend CRGB operator*=(CRGB &, CRGB &);
	friend CRGB operator/=(CRGB &, double);
	void   Normalize();
public:
	double red;//红色分量
	double green;//绿色分量
	double blue;//蓝色分量
};

