
// qiuView.cpp: CqiuView 类的实现
//

#include "pch.h"
#include "framework.h"
//#include"OpenGLInit.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "qiu.h"
#endif

#include "qiuDoc.h"
#include "qiuView.h"
#include<fstream>

#define BMP_Header_Length 54
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define _USE_MATH_DEFINES
#include<math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CqiuView

IMPLEMENT_DYNCREATE(CqiuView, CView)

BEGIN_MESSAGE_MAP(CqiuView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CqiuView 构造/析构

CqiuView::CqiuView() noexcept
{
	//xTranBool = TRUE;
	//yTranBool = TRUE;
	//zTranBool = TRUE;

	Dis = 0.0f;
	//Moon_R = 0.0f;
	//Earth_R = 0.0f;

	Moon_X = 0.0f;
	Moon_Y = 0.0f;
	Moon_Z = 10.0f;

	Rotate_Moon_Self = 0.0f;
	Rotate_Moon_Surr = 0.0f;
	Rotate_Earth_Self = 0.0f;
	Dis = 10.0f;
	Pattern = 0;
	Lighting = 0;
	Blank = 0;
	uiTextures[0] = 0;
	uiTextures[1] = 0;
	texture = 0;
	earth = new ball;
	moon = new ball(3);
	earth_2 = new CSphere;

	// TODO: 在此处添加构造代码

}

CqiuView::~CqiuView()
{

}

BOOL CqiuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CqiuView 绘图

void CqiuView::OnDraw(CDC* /*pDC*/)
{
	CqiuDoc* pDoc = (CqiuDoc*)CView::GetDocument();
	ASSERT_VALID(pDoc);

	DrawScene();

	// TODO: 在此处为本机数据添加绘制代码
}


// CqiuView 打印

BOOL CqiuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CqiuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CqiuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CqiuView 诊断

#ifdef _DEBUG
void CqiuView::AssertValid() const
{
	CView::AssertValid();
}

void CqiuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
/*
CqiuDoc* CqiuView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CqiuDoc)));
	return (CqiuDoc*)m_pDocument;
}*/
#endif //_DEBUG


// CqiuView 消息处理程序



void CqiuView::DrawScene()
{
	//在屏幕上显出图形
	if (m_hglrc)					//设置当前绘图设备为OpenGL的设备情景对象
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hglrc);
	else
		return;

	glDrawBuffer(GL_BACK);		//指定在后台缓存中绘制图形
	glLoadIdentity();			//初始化变换矩阵

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glShadeModel(GL_SMOOTH);



	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, uiTextures[0]);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glBindTexture(GL_TEXTURE_2D, uiTextures[1]);
	//变换
	glTranslated(Moon_X, 0.0, 0.0);
	glTranslated(0.0, Moon_Y, 0.0);
	glTranslated(0.0, 0.0, Moon_Z);

	//glRotated(RotateX, 1.0, 0.0, 0.0);
	glRotated(Rotate_Moon_Self, 0.0, 1.0, 0.0);
	//glRotated(RotateZ, 0.0, 0.0, 1.0);

	//画图
	moon->DrawGeometry();
	glPopMatrix();
	glPushMatrix();
	//glRotated(RotateX, 1.0, 0.0, 0.0);
	//glRotated(RotateY, 0.0, 1.0, 0.0);
	glRotated(Rotate_Earth_Self, 0.0, 1.0, 0.0);
	glBindTexture(GL_TEXTURE_2D, uiTextures[0]);
	if (Pattern)
		earth_2->Draw();
	else
		earth->DrawGeometry();
	glPopMatrix();
	glFinish();					//结束整个绘制
	SwapBuffers(wglGetCurrentDC());	//交换前后缓存
	glDrawBuffer(GL_FRONT);			//绘制前景
}

GLuint CqiuView::load_texture(const char* file_name)
{

	//多边形正面材料环境和散射颜色 追踪glcolor
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	//启用颜色追踪
	glEnable(GL_COLOR_MATERIAL);

	GLint width, height, total_bytes;
	GLuint last_texture_ID = 0, texture_ID = 0;
	unsigned char* data = stbi_load(file_name, &width, &height, &total_bytes, 0);
	// 分配一个新的纹理编号
	glGenTextures(1, &texture_ID);
	// 绑定新的纹理，载入纹理并设置纹理参数
	// 在绑定前，先获得原来绑定的纹理编号，以便在最后进行恢复
	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//GLfloat blendColor[] = { 0.2, 0.3, 0.0, 0.5 };
	//glTexEnvfv(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, blendColor);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //恢复之前的纹理绑定
	stbi_image_free(data);
	//free(pixels);
	return texture_ID;
}

int CqiuView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_pDC = new CClientDC(this);
	ASSERT(m_pDC != NULL);
	if (!OpenGLInit(m_pDC, m_hglrc))		//初始化OpenGL的显示情况
		return -1;
	GLfloat LightAmbient[] = { 1.0f, 0.0f, 0.0f };                      // 环境光   
	GLfloat LightDiffuse[] = { 1.0f, 0.0f, 0.0f };                      // 漫射光   
	GLfloat LightPosition[] = { 10.0f, 10.0f, 2.0f };                      // 光源位置   
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT0);
	uiTextures[0] = load_texture("bumptexture.bmp");
	uiTextures[1] = load_texture("moon.bmp");
	SetTimer(0, 30, NULL);
	// TODO:  在此添加您专用的创建代码
	//glDisable(GL_LIGHT1);
	return 0;
}


void CqiuView::OnDestroy()
{
	OpenGLExit(m_pDC, m_hglrc);
	CView::OnDestroy();
	glDeleteTextures(1, &(uiTextures[0]));
	glDeleteTextures(1, &(uiTextures[1]));
	if (earth != nullptr) {
		delete earth;
		earth = nullptr;
	}
	if (moon != nullptr) {
		delete moon;
		moon = nullptr;
	}
	if (earth_2 != nullptr) {
		delete earth_2;
		earth_2 = nullptr;
	}

	// TODO: 在此处添加消息处理程序代码
}


void CqiuView::OnTimer(UINT_PTR nIDEvent)
{
	CqiuDoc* pDoc = (CqiuDoc*)CView::GetDocument();

	Rotate_Moon_Self += pDoc->RotateX;
	Rotate_Moon_Surr += pDoc->RotateY;
	Rotate_Earth_Self += pDoc->RotateZ;
	Dis = pDoc->Earth_R+pDoc->Dis;
	Moon_X = cos(-Rotate_Moon_Surr / 180 * 3.1415926) * Dis;
	Moon_Y = 0.0f;
	Moon_Z = sin(-Rotate_Moon_Surr / 180 * 3.1415926) * Dis;
	if (pDoc->moon_change) {
		moon->setRadius(pDoc->Moon_R);
		pDoc->moon_change = false;
	}
	if (pDoc->earth_change) {
		earth->setRadius(pDoc->Earth_R);
		CSphere* temp = earth_2;
		earth_2 = new CSphere(pDoc->Earth_R);
		delete temp;
		//earth_2->setRadius(pDoc->Earth_R);
		pDoc->earth_change = false;
	}

	if (pDoc->lighting)
	{
		glEnable(GL_LIGHT0);
	}
	else {
		glDisable(GL_LIGHT0);
	}
	
	Pattern = pDoc->Pattern;

	InvalidateRect(NULL, FALSE);	//视图重绘，调用了OnDraw()


	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CView::OnTimer(nIDEvent);
}


void CqiuView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
		//设置视口大小
	glViewport(0, 0, cx, cy);

	glMatrixMode(GL_PROJECTION);	//投影变换
	glLoadIdentity();

	if (cx <= cy)	//根据窗口大小调整正射投影矩阵
		//glFrustum(-20.0, 20.0, -20.0 * (GLfloat)cy / (GLfloat)cx, 20.0 * (GLfloat)cy / (GLfloat)cx, 5.0, 40.0);
		glOrtho(-20.0, 20.0, -20.0 * (GLfloat)cy / (GLfloat)cx, 20.0 * (GLfloat)cy / (GLfloat)cx, -50.0, 50.0);
	else
		//glFrustum(-20.0 * (GLfloat)cx / (GLfloat)cy, 20.0 * (GLfloat)cx / (GLfloat)cy, -20.0, 20.0, 5.0, 40.0);
		glOrtho(-20.0 * (GLfloat)cx / (GLfloat)cy, 20.0 * (GLfloat)cx / (GLfloat)cy, -20.0, 20.0, -50.0, 50.0);

	glMatrixMode(GL_MODELVIEW);		//这二句不能少，否则图形看不出效果
	glLoadIdentity();				//设置变换模式为模型变换
}


BOOL OpenGLInit(CClientDC* pDC, HGLRC& hglrc)
{
	int n;								//当前选择的像素格式索引

	static PIXELFORMATDESCRIPTOR pfd =
	{									//像素点格式信息描述结构体
		sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW |		//支持Windows与OpenGL二环境绘图
			PFD_SUPPORT_OPENGL |
			PFD_DOUBLEBUFFER,			//使用双缓存交换显示图形
			PFD_TYPE_RGBA,			    // RGBA type 
			24,							// 24-bit color depth 
			0, 0, 0, 0, 0, 0,			// color bits ignored 
			0,							// no alpha buffer 
			0,							// shift bit ignored 
			0,							// no accumulation buffer 
			0, 0, 0, 0,					// accum bits ignored 
			32,							// 32-bit z-buffer     
			0,							// no stencil buffer 
			0,							// no auxiliary buffer 
			PFD_MAIN_PLANE,				// main layer 
			0,							// reserved 
			0, 0, 0						// layer masks ignored 
	};

	int pixelformat;
	if ((pixelformat = ChoosePixelFormat(pDC->GetSafeHdc(), &pfd)) == 0)
	{
		AfxMessageBox(_T("选择像素格式化失败"));
		return FALSE;
	}

	if (SetPixelFormat(pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		AfxMessageBox(_T("设置像素格式化失败"));
		return FALSE;
	}

	n = ::GetPixelFormat(pDC->GetSafeHdc());
	::DescribePixelFormat(pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);

	hglrc = wglCreateContext(pDC->GetSafeHdc());	//创建绘制情景对象

	wglMakeCurrent(pDC->GetSafeHdc(), hglrc);		//选择绘制情景对象

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);

	//	glMatrixMode(GL_MODELVIEW);						//设置变换模式为模型变换
	//	glLoadIdentity();								//初始化模型变换矩阵
	return TRUE;
}

BOOL OpenGLExit(CClientDC* pDC, HGLRC& hglrc)
{
	::wglMakeCurrent(NULL, NULL);		//将当前绘图情景对象置空

	if (hglrc)
		::wglDeleteContext(hglrc);		//删除当前绘图情景对象

	if (pDC)
		delete pDC;					//删除创建的windows设备上下文

	return TRUE;
}


