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
	float Mag();//ʸ����ģ
	CVector3 Normalize();//��λʸ��
	friend CVector3 operator +(const CVector3&, const CVector3&);//���������
	friend CVector3 operator -(const CVector3&, const CVector3&);
	friend CVector3 operator *(const CVector3&, float);
	friend CVector3 operator *(float, const CVector3&);
	friend CVector3 operator /(const CVector3&, float);
	friend CVector3 operator+=(CVector3&, CVector3&);
	friend CVector3 operator-=(CVector3&, CVector3&);
	friend CVector3 operator*=(CVector3&, CVector3&);
	friend CVector3 operator/=(CVector3&, float);
	friend float  Dot(const CVector3&, const CVector3&);  //ʸ�����
	friend CVector3 Cross(const CVector3&, const CVector3&);//ʸ�����
public:
	float x, y, z;//�������ݳ�Ա�������ⲿ����
};

