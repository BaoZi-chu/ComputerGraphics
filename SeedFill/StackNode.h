#pragma once
class CStackNode//ջ���
{
public:
	CStackNode();
	virtual ~CStackNode();
public:
	CPoint PixelPoint;
	CStackNode* pNext;
};

