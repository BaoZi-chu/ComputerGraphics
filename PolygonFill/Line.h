#pragma once
#include "CP2.h"
#include "CRGB.h"
class CLine
{
public:
	CLine();
	virtual ~CLine();
	void MoveTo(CDC*, CP2);//移动到指定位置
	void MoveTo(CDC*, double, double);
	void LineTo(CDC*, CP2);//绘制直线，不含终点
	void LineTo(CDC*, double, double);
public:
	CP2 P0;//起点
	CP2 P1;//终点
};

