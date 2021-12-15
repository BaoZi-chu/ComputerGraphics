#include "pch.h"
#include "Vector3.h"
#include "math.h"

CVector3::CVector3()//z������
{
	x = 0.0;
	y = 0.0;
	z = 1.0;
}

CVector3::~CVector3()
{

}

CVector3::CVector3(const CP3d& p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}

CVector3::CVector3(const CPi3& p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}

CVector3::CVector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

CVector3::CVector3(const CP3d& p0, const CP3d& p1)
{
	x = p1.x - p0.x;
	y = p1.y - p0.y;
	z = p1.z - p0.z;
}

CVector3::CVector3(const CPi3& p0, const CPi3& p1)
{
	x = p1.x - p0.x;
	y = p1.y - p0.y;
	z = p1.z - p0.z;
}

float CVector3::Mag()//ʸ����ģ
{
	return sqrt(x * x + y * y + z * z);
}

CVector3 CVector3::Normalize()//��һ������λʸ��
{
	CVector3 vector;
	float Mag = sqrt(x * x + y * y + z * z);
	if (fabs(Mag) < 1e-6)
		Mag = 1.0;
	vector.x = x / Mag;
	vector.y = y / Mag;
	vector.z = z / Mag;
	return vector;
}

CVector3 operator +(const CVector3& v0, const CVector3& v1)//ʸ���ĺ�
{
	CVector3 vector;
	vector.x = v0.x + v1.x;
	vector.y = v0.y + v1.y;
	vector.z = v0.z + v1.z;
	return vector;
}

CVector3 operator -(const CVector3& v0, const CVector3& v1)//ʸ���Ĳ�
{
	CVector3 vector;
	vector.x = v0.x - v1.x;
	vector.y = v0.y - v1.y;
	vector.z = v0.z - v1.z;
	return vector;
}

CVector3 operator *(const CVector3& v, float k)//ʸ���볣���Ļ�
{
	CVector3 vector;
	vector.x = v.x * k;
	vector.y = v.y * k;
	vector.z = v.z * k;
	return vector;
}

CVector3 operator *(float k, const CVector3& v)//������ʸ���Ļ�
{
	CVector3 vector;
	vector.x = v.x * k;
	vector.y = v.y * k;
	vector.z = v.z * k;
	return vector;
}

CVector3 operator /(const CVector3& v, float k)//ʸ������
{
	if (fabs(k) < 1e-6)
		k = 1.0;
	CVector3 vector;
	vector.x = v.x / k;
	vector.y = v.y / k;
	vector.z = v.z / k;
	return vector;
}

CVector3 operator +=(CVector3& v0, CVector3& v1)//+=���������
{
	v0.x = v0.x + v1.x;
	v0.y = v0.y + v1.y;
	v0.z = v0.z + v1.z;
	return v1;
}

CVector3 operator -=(CVector3& v0, CVector3& v1)//-=���������
{
	v0.x = v0.x - v1.x;
	v0.y = v0.y - v1.y;
	v0.z = v0.z - v1.z;
	return v0;
}

CVector3 operator *=(CVector3& v0, CVector3& v1)//*=���������
{
	v0.x = v0.x * v1.x;
	v0.y = v0.y * v1.y;
	v0.z = v0.z * v1.z;
	return v0;
}

CVector3 operator /=(CVector3& v, float k)///=���������
{
	v.x = v.x / k;
	v.y = v.y / k;
	v.z = v.z / k;
	return v;
}

float Dot(const CVector3& v0, const CVector3& v1)//ʸ���ĵ��
{
	return(v0.x * v1.x + v0.y * v1.y + v0.z * v1.z);
}

CVector3 Cross(const CVector3& v0, const CVector3& v1)//ʸ���Ĳ��
{
	CVector3 vector;
	vector.x = v0.y * v1.z - v0.z * v1.y;
	vector.y = v0.z * v1.x - v0.x * v1.z;
	vector.z = v0.x * v1.y - v0.y * v1.x;
	return vector;
}