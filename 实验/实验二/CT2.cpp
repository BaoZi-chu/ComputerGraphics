#include "pch.h"
#include "CT2.h"
#include "math.h"

CT2::CT2()
{
	u = 0;
	v = 0;
}

CT2::~CT2()
{
}

CT2::CT2(float u, float vv)
{
	this->u = u;
	this->v = v;
}

CT2 operator +(const CT2& t1, const CT2& t2)//��
{
	CT2 t;
	t.u = t1.u + t2.u;
	t.v = t1.v + t2.v;
	return t;
}

CT2 operator -(const CT2& t1, const CT2& t2)//��
{
	CT2 t;
	t.u = t1.u - t2.u;
	t.v = t1.v - t2.v;
	return t;
}

CT2 operator *(const CT2& t, float k)//��ͳ����Ļ�
{
	return CT2(t.u * k, t.v * k);
}

CT2 operator *(float k, const CT2& t)//��ͳ����Ļ�
{
	return CT2(t.u * k, t.v * k);
}

CT2 operator /(const CT2& t1, float k)//����
{
	if (fabs(k) < 1e-6)
		k = 1.0;
	CT2 t;
	t.u = t1.u / k;
	t.v = t1.v / k;
	return t;
}

CT2 operator+=(CT2& t1, CT2& t2)
{
	t1.u = t1.u + t2.u;
	t1.v = t1.v + t2.v;
	return t1;
}

CT2 operator-=(CT2& t1, CT2& t2)
{
	t1.u = t1.u - t2.u;
	t1.v = t1.v - t2.v;
	return t1;
}

CT2 operator*=(CT2& t1, float k)
{
	t1.u = t1.u * k;
	t1.v = t1.v * k;
	return t1;
}

CT2 operator/=(CT2& t1, float k)
{
	if (fabs(k) < 1e-6)
		k = 1.0;
	t1.u = t1.u / k;
	t1.v = t1.v / k;
	return t1;
}