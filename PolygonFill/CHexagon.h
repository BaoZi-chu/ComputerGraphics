#pragma once
#include "Fill.h"//包含填充类
#include "Line.h"//包含直线类
class CHexagon
{
public:
	CHexagon();
	virtual~CHexagon();
	void ReadPoint();//读入顶点表
	void DrawPolygon(CDC* pDC);//绘制多边形
	void FillPolygon(CDC* pDC);//填充多边形
	int n;
public:
	CP2 P[9];//浮点点表
	CPi2 P0[9];//y整数点表
	BYTE bRed, bGreen, bBlue;//颜色分量
	BOOL bFill;//填充标志 
};

