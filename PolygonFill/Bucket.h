#pragma once
#include "AET.h"
class CBucket
{
public:
	CBucket();
	virtual ~CBucket();
public:
	int     ScanLine;     //ɨ����
	CAET* pET;         //Ͱ�ϵı߱�ָ��
	CBucket* pNext;
};

