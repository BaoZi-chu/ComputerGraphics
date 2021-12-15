#pragma once
class CStackNode//Õ»½áµã
{
public:
	CStackNode();
	virtual ~CStackNode();
public:
	CPoint PixelPoint;
	CStackNode* pNext;
};

