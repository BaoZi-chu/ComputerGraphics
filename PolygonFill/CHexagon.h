#pragma once
#include "Fill.h"//���������
#include "Line.h"//����ֱ����
class CHexagon
{
public:
	CHexagon();
	virtual~CHexagon();
	void ReadPoint();//���붥���
	void DrawPolygon(CDC* pDC);//���ƶ����
	void FillPolygon(CDC* pDC);//�������
	int n;
public:
	CP2 P[9];//������
	CPi2 P0[9];//y�������
	BYTE bRed, bGreen, bBlue;//��ɫ����
	BOOL bFill;//����־ 
};

