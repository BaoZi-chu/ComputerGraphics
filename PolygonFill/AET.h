#pragma once
#include "CPi2.h"

class CAET
{
public:
	CAET();
	virtual ~CAET();
public:
	double  x;//��ǰɨ��������Ч�߽����x����
	int     yMax;//�ߵ����yֵ
	double  k;//б�ʵĵ���(x������)
	CPi2    ps;//�ߵ����
	CPi2    pe;//�ߵ��յ�
	CAET* pNext;
};

