#pragma once
#include "CT2.h"
#include "Vector3.h"

class CFace
{
public:
	CFace();
	virtual ~CFace();
	void SetNum(int vN);//����С��Ķ�����
	void SetFaceNormal(CP3d, CP3d, CP3d);//����С�淨ʸ��
public:
	int vN;          //С��Ķ�����
	int *vI;         //С��Ķ�������
	CVector3 fNormal; //С��ķ�ʸ��
	CT2 *t;          //�����㶯̬����
};

