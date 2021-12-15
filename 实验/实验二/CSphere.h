#pragma once
#include"P3d.h"
#include"CT2.h"
#include"Face.h"
class CSphere
{
public:
	CSphere();
	CSphere(float radius);
	virtual~CSphere();
	void ReadVertex();//���붥������
	void ReadFace();//����������
	void Draw();//��������
	void setRadius(float radius);
public:
	CP3d* V;//Բ������һά����
	CP3d* V1;
	CT2* T;//Բ������һά����
	CT2* T1;
	CFace** F;//��Ķ�ά����
	int N1, N2;//N1Ϊ��������,N2Ϊγ������
	int N3, N4;
	int gAlpha, gBeta;//γ�Ƚ��뾭�Ƚ�
	int gA1pha1, gBeta1;
	float r;//����뾶
private:
	//void GetGeometry(float radius);
	void initial();
	void tran(CVector3 p, float* v) {

		v[0] = p.x;
		v[1] = p.y;
		v[2] = p.z;

	}
};

