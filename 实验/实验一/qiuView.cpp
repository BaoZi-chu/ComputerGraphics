
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
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CqiuView 构造/析构

CqiuView::CqiuView() noexcept
{
	xTranBool = TRUE;
	yTranBool = TRUE;
	zTranBool = TRUE;

	TranslateX = 0.0f;
	TranslateY = 0.0f;
	TranslateZ = 0.0f;

	RotateX = 0.0f;
	RotateY = 0.0f;
	RotateZ = 0.0f;
	Radius = 10.0;
	Pattern = 0;
	Count = 4;
	Lighting = 0;
	Blank = 0;
	uiTextures = 0;
	texture = 0;
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

void CqiuView::NormalTriangle(float* v1, float* v2, float* v3, float* vout)
{
	//求三点构成的三角形面的法向量
	GLfloat v12[3], v23[3];
	for (int i = 0; i < 3; i++) {
		v12[i] = v2[i] - v1[i];
		v23[i] = v3[i] - v2[i];
	}

	vout[0] = v12[1] * v23[2] - v12[2] * v23[1];
	vout[1] = -(v12[0] * v23[2] - v12[2] * v23[0]);
	vout[2] = v12[0] * v23[1] - v12[1] * v23[0];
	Normalize(vout, 1);
}

void CqiuView::Normalize(float* v, float radius)
{
	//向量的标准化,以模长为radius进行标准化
	GLfloat d = (GLfloat)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (d == 0.0) {
		return;
	}
	v[0] /= d; v[1] /= d; v[2] /= d;
	v[0] *= radius; v[1] *= radius; v[2] *= radius;
}

void CqiuView::DrawTriangle(float* v1, float* v2, float* v3)
{
	//以三点为顶点画三角形
	GLfloat normal[3] = { 0,0,0 };
	NormalTriangle(v1, v2, v3, normal);//求取面法向量
	glBegin(Pattern);
	glNormal3fv(normal);
	

	if (0 == Blank) {
	glVertex3fv(v1);
	glVertex3fv(v2);
	glVertex3fv(v3);
	}else{
	glTexCoord2f(0.0, 0.0); glVertex3fv(v1);
	glTexCoord2f(0.0, 1.0); glVertex3fv(v2);
	glTexCoord2f(1.0, 0.5); glVertex3fv(v3);
	}
	glEnd();
}

void CqiuView::SubDivide(float* v1, float* v2, float* v3, int count)
{
	//把count为级数，对一个三角形面的子划分
	if (0 >= count)	//count=0,则画由三点构成的三角形
	{
		DrawTriangle(v1, v2, v3);
	}
	else
	{
		GLfloat v12[3], v23[3], v31[3];
		GLint i;
		for (i = 0; i < 3; i++) {
			v12[i] = (v1[i] + v2[i]) / 2;
			v23[i] = (v2[i] + v3[i]) / 2;
			v31[i] = (v3[i] + v1[i]) / 2;
		}
		Normalize(v12, (float)Radius);	//扩展模长
		Normalize(v23, (float)Radius);
		Normalize(v31, (float)Radius);

		SubDivide(v1, v12, v31, count - 1);
		SubDivide(v2, v23, v12, count - 1);
		SubDivide(v3, v31, v23, count - 1);
		SubDivide(v12, v23, v31, count - 1);
	}
}

void CqiuView::DrawGeometry()
{
	//在此处画球体
	GLfloat r = (GLfloat)Radius;
	GLfloat vdata[6][3] = {	//初始点坐标
		{r,0.0,0.0},{-r,0.0,0.0},
		{0.0,r,0.0},{0.0,-r,0.0},
		{0.0,0.0,r},{0.0,0.0,-r}
	};
	GLuint tindices[8][3] = {//初始面的构造
		{2,4,0},{2,0,5},{2,5,1},{2,1,4},
		{3,0,4},{3,5,0},{3,1,5},{3,4,1}
	};

	/*以下坐标是参考书上的初值,为正20面体,效果会比自定义的要好些
	const float X = (float)0.525731112119133606*m_nRadius;
	const float Z = (float)0.850650808352039932*m_nRadius;
	static GLfloat vdata[12][3] = {
		{-X,0.0,Z},{X,0.0,Z},{-X,0.0,-Z},{X,0.0,-Z},
		{0.0,Z,X},{0.0,Z,-X},{0.0,-Z,X},{0.0,-Z,-X},
		{Z,X,0.0},{-Z,X,0.0},{Z,-X,0.0},{-Z,-X,0.0}
	};
	static GLuint tindices[20][3] = {
		{0,4,1},{0,9,4},{9,5,4},{4,5,8},{4,8,1},
		{8,10,1},{8,3,10},{5,3,8},{5,2,3},{2,7,3},
		{7,10,3},{7,6,10},{7,11,6},{11,0,6},{0,1,6},
		{6,1,10},{9,0,11},{9,11,2},{9,2,5},{7,2,11}
	};*/

	for (int i = 0; i < 8; i++) {
		SubDivide(&vdata[tindices[i][0]][0],
			&vdata[tindices[i][1]][0],
			&vdata[tindices[i][2]][0],Count);
	}
}


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
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);


	glPushMatrix();
	glShadeModel(GL_SMOOTH);

	//光照
	GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat mat_specular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_shininess[] = { 50.0f };

	GLfloat light_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);//材质的环境颜色
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);//材质的散射颜色
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);//材质的镜面反射颜色
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);//镜面反射指数

	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	if (0 == Lighting)
		glDisable(GL_LIGHTING);
	else
		glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	if (0 == Blank)
		glDisable(GL_TEXTURE_2D);
	else
	{ 
		glEnable(GL_TEXTURE_2D);
	}
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	//变换
	glTranslated(TranslateX, 0.0, 0.0);
	glTranslated(0.0, TranslateY, 0.0);
	glTranslated(0.0, 0.0, TranslateZ);

	glRotated(RotateX, 1.0, 0.0, 0.0);
	glRotated(RotateY, 0.0, 1.0, 0.0);
	glRotated(RotateZ, 0.0, 0.0, 1.0);

	//画图
	DrawGeometry();
	//画图结束
	glPopMatrix();
	glFinish();					//结束整个绘制
	SwapBuffers(wglGetCurrentDC());	//交换前后缓存
	glDrawBuffer(GL_FRONT);			//绘制前景
}

GLuint CqiuView::load_texture(const char* file_name)
{
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
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
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
	uiTextures = load_texture("container.jpg");
	glBindTexture(GL_TEXTURE_2D, uiTextures);
	SetTimer(0, 30, NULL);
	// TODO:  在此添加您专用的创建代码
	
	return 0;
}


void CqiuView::OnDestroy()
{
	OpenGLExit(m_pDC, m_hglrc);
	CView::OnDestroy();
	glDeleteTextures(1, &uiTextures);
	// TODO: 在此处添加消息处理程序代码
}


void CqiuView::OnTimer(UINT_PTR nIDEvent)
{
	CqiuDoc* pDoc = (CqiuDoc*)CView::GetDocument();

	RotateX += pDoc->RotateX;
	RotateY += pDoc->RotateY;
	RotateZ += pDoc->RotateZ;

	if (TranslateX > 15) {
		xTranBool = false;
	}
	else if (TranslateX < -15) {
		xTranBool = true;
	}
	if (xTranBool)
		TranslateX += pDoc->TranslateX;
	else
		TranslateX -= pDoc->TranslateX;


	if (TranslateY > 10) {
		yTranBool = false;
	}
	else if (TranslateY < -10) {
		yTranBool = true;
	}
	if (yTranBool)
		TranslateY += pDoc->TranslateY;
	else
		TranslateY -= pDoc->TranslateY;

	if (TranslateZ > 10) {
		zTranBool = false;
	}
	else if (TranslateZ < -10) {
		zTranBool = true;
	}
	if (zTranBool)
		TranslateZ += pDoc->TranslateZ;
	else
		TranslateZ -= pDoc->TranslateZ;

	Radius = pDoc->Radius;
	Count = pDoc->Count;
	Lighting = pDoc->Lighting;
	Blank = pDoc->Blank;
	if (0 == pDoc->Pattern)
		Pattern = GL_LINE_LOOP;
	else
		Pattern = GL_TRIANGLES;

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
		glOrtho(-20.0, 20.0, -20.0 * (GLfloat)cy / (GLfloat)cx,20.0 * (GLfloat)cy / (GLfloat)cx, -50.0, 50.0);
	else
		//glFrustum(-20.0 * (GLfloat)cx / (GLfloat)cy, 20.0 * (GLfloat)cx / (GLfloat)cy, -20.0, 20.0, 5.0, 40.0);
		glOrtho(-20.0 * (GLfloat)cx / (GLfloat)cy,20.0 * (GLfloat)cx / (GLfloat)cy, -20.0, 20.0, -50.0, 50.0);

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

BOOL CqiuView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
		if (zDelta > 0 && Radius < 20)
			Radius++;
		if(zDelta<0&&Radius>1)
			Radius--;
		CqiuDoc* pDoc = (CqiuDoc*)CqiuView::GetDocument();
		pDoc->Radius = Radius;
		pDoc->UpdateAllViews(this);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
