
// qiuView.h: CqiuView 类的接口
//

#pragma once
#include<GL/glut.h>
#include"ball.h"
#include"CSphere.h"
BOOL OpenGLInit(CClientDC* pDC, HGLRC& hglrc);
BOOL OpenGLExit(CClientDC* pDC, HGLRC& hglrc);
class CqiuView : public CView
{
protected: // 仅从序列化创建
	CqiuView() noexcept;
	DECLARE_DYNCREATE(CqiuView)

// 特性
public:
	//CqiuDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CqiuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
//自定义
public:
	HGLRC m_hglrc;
	CClientDC* m_pDC;
private:
	UINT Pattern;
	GLuint Lighting;
	GLuint Blank;
	float Dis;
	GLfloat Moon_X;
	GLfloat Moon_Y;
	GLfloat Moon_Z;
	GLfloat Rotate_Moon_Self;
	GLfloat Rotate_Moon_Surr;
	GLfloat Rotate_Earth_Self;
	GLuint uiTextures[2];
	ball* earth;
	ball* moon;
	CSphere* earth_2;
	
unsigned int texture;
protected:
	void DrawScene();
	int power_of_two(int n)
	{
		if (n <= 0)
			return 0;
		return (n & (n - 1)) == 0;
	}

	GLuint load_texture(const char* file_name);
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // qiuView.cpp 中的调试版本
inline CqiuDoc* CqiuView::GetDocument() const
   { return reinterpret_cast<CqiuDoc*>(m_pDocument); }
#endif

