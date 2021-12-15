#pragma once
#include "Bucket.h"

class CFill
{
public:
	CFill(void);
	virtual ~CFill(void);
	void SetPoint(CPi2* p, int);//��ĳ�ʼ��
	void CreateBucket();//����Ͱ
	void CreateEdge();//�߱�
	void AddEt(CAET*);//�ϲ�ET��
	void EtOrder();//ET������
	void Gouraud(CDC*);//�������
	CRGB Interpolation(double, double, double, CRGB, CRGB);//���Բ�ֵ
	void ClearMemory();//�����ڴ�
	void DeleteAETChain(CAET* pAET);//ɾ���߱�
public:
	int     PNum;//�������
	CPi2* P;//�������궯̬����
	CAET* pHeadE, * pCurrentE, * pEdge; //��Ч�߱���ָ��
	CBucket* pHeadB, * pCurrentB;        //Ͱ����ָ��
};

