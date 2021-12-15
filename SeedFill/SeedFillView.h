
// SeedFillView.h: CSeedFillView 类的接口
//
#include"StackNode.h"
#pragma once


class CSeedFillView : public CView
{
protected: // 仅从序列化创建
	CSeedFillView() noexcept;
	DECLARE_DYNCREATE(CSeedFillView)

// 特性
public:
	CSeedFillDoc* GetDocument() const;

// 操作
public:
	void DoubleBuffer(CDC* pDC);	//双缓冲绘图
	void BoundaryFill();			//边界填充算法
	void Push(CPoint point);		//入栈
	void Pop(CPoint& point);		//出栈

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	int nClientWidth, nClientHeight;//屏幕客户区宽度和高度
	int nHWidth, nHHeight;//屏幕客户区的半宽和半高
	COLORREF SeedClr, BoundaryClr, BkClr;//种子颜色、边界颜色和背景色
	CStackNode* pHead, * pTop;//结点指针
	CPoint Seed, Left, Top, Right, Bottom;//种子及其四个邻接点

// 实现
public:
	virtual ~CSeedFillView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // SeedFillView.cpp 中的调试版本
inline CSeedFillDoc* CSeedFillView::GetDocument() const
   { return reinterpret_cast<CSeedFillDoc*>(m_pDocument); }
#endif

