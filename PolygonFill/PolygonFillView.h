﻿
// PolygonFillView.h: CPolygonFillView 类的接口
//

#pragma once
#include"CHexagon.h"

class CPolygonFillView : public CView
{
protected: // 仅从序列化创建
	CPolygonFillView() noexcept;
	DECLARE_DYNCREATE(CPolygonFillView)

// 特性
public:
	CPolygonFillDoc* GetDocument() const;

// 操作
public:
	void DrawGraph();//绘制图形
// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CPolygonFillView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CHexagon hex;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // PolygonFillView.cpp 中的调试版本
inline CPolygonFillDoc* CPolygonFillView::GetDocument() const
   { return reinterpret_cast<CPolygonFillDoc*>(m_pDocument); }
#endif

