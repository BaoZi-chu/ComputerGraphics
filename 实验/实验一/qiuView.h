
// qiuView.h: CqiuView 类的接口
//

#pragma once
#include<GL/glut.h>

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
	GLuint Radius;
	GLuint Count;
	GLuint Pattern;
	GLuint Lighting;
	GLuint Blank;
	GLfloat TranslateX;
	GLfloat TranslateY;
	GLfloat TranslateZ;
	GLfloat RotateX;
	GLfloat RotateY;
	GLfloat RotateZ;
	BOOL  xTranBool;
	BOOL  yTranBool;
	BOOL  zTranBool;
	GLuint uiTextures;
unsigned int texture;
protected:
	void NormalTriangle(float* v1, float* v2, float* v3, float* vout);
	void Normalize(float* v, float radius);
	void DrawTriangle(float* v1, float* v2, float* v3);
	void SubDivide(float* v1, float* v2, float* v3, int count);
	void DrawGeometry();
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

	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // qiuView.cpp 中的调试版本
inline CqiuDoc* CqiuView::GetDocument() const
   { return reinterpret_cast<CqiuDoc*>(m_pDocument); }
#endif

