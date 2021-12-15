#pragma once
#include "P3d.h"
#include "Pi3.h"
class CVector3
{
public:
	CVector3();
	virtual ~CVector3();
	CVector3(float x, float y, float z);
	CVector3(const CP3d&);
	CVector3(const CPi3&);
	CVector3(const CP3d&, const CP3d&);
	CVector3(const CPi3&, const CPi3&);
	float Mag();//矢量的模
	CVector3 Normalize();//单位矢量
	friend CVector3 operator +(const CVector3&, const CVector3&);//运算符重载
	friend CVector3 operator -(const CVector3&, const CVector3&);
	friend CVector3 operator *(const CVector3&, float);
	friend CVector3 operator *(float, const CVector3&);
	friend CVector3 operator /(const CVector3&, float);
	friend CVector3 operator+=(CVector3&, CVector3&);
	friend CVector3 operator-=(CVector3&, CVector3&);
	friend CVector3 operator*=(CVector3&, CVector3&);
	friend CVector3 operator/=(CVector3&, float);
	friend float  Dot(const CVector3&, const CVector3&);  //矢量点积
	friend CVector3 Cross(const CVector3&, const CVector3&);//矢量叉积
public:
	float x, y, z;//公有数据成员，方便外部访问
};

