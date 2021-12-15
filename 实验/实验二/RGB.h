#pragma once
class CRGB
{
public:
	CRGB();
	CRGB(double, double, double);
	virtual ~CRGB();
	friend CRGB operator+(CRGB &, CRGB &);//���������
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
	double red;//��ɫ����
	double green;//��ɫ����
	double blue;//��ɫ����
};

