// LEFT_OPTION.cpp: 实现文件
//

#include "pch.h"
#include "qiu.h"
#include "LEFT_OPTION.h"
#include "qiuDoc.h"


// LEFT_OPTION

IMPLEMENT_DYNCREATE(LEFT_OPTION, CFormView)

LEFT_OPTION::LEFT_OPTION()
	: CFormView(ID_LEFT_VIEW)
	, nPattern(-1)
	, light(FALSE)
{

}

LEFT_OPTION::~LEFT_OPTION()
{
}

void LEFT_OPTION::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_X_ROTA_SLIDER, cRotateX);
	DDX_Control(pDX, IDC_X_TRAN_SLIDER, cTranslateX);
	DDX_Control(pDX, IDC_Y_ROTA_SLIDER, cRotateY);
	DDX_Control(pDX, IDC_Y_TRAN_SLIDER, cTranslateY);
	DDX_Control(pDX, IDC_Z_TRAN_SLIDER, cTranslateZ);
	DDX_Control(pDX, IDC_Z_ROTA_SLIDER, cRotateZ);
	DDX_Radio(pDX, IDC_Pattern_1, nPattern);

	DDX_Radio(pDX, IDC_Lighting_1, light);
}

BEGIN_MESSAGE_MAP(LEFT_OPTION, CFormView)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_Pattern_1, &LEFT_OPTION::OnBnClickedPattern1)
	ON_BN_CLICKED(IDC_Pattern_2, &LEFT_OPTION::OnBnClickedPattern2)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_Lighting_1, &LEFT_OPTION::OnBnClickedLighting1)
	ON_BN_CLICKED(IDC_Lighting_2, &LEFT_OPTION::OnBnClickedLighting2)
END_MESSAGE_MAP()


// LEFT_OPTION 诊断

#ifdef _DEBUG
void LEFT_OPTION::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void LEFT_OPTION::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// LEFT_OPTION 消息处理程序




void LEFT_OPTION::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类
	light = 1;
	nPattern = 0;
	cTranslateX.SetRange(10, 20);
	cTranslateY.SetRange(0, 10);
	cTranslateZ.SetRange(0, 10);
	cTranslateX.SetPos(10);
	cTranslateY.SetPos(1);
	cTranslateZ.SetPos(1);
	cRotateX.SetRange(0, 10);
	cRotateY.SetRange(0, 10);
	cRotateZ.SetRange(0, 10);
	cRotateX.SetPos(2);
	cRotateY.SetPos(5);
	cRotateZ.SetPos(3);
	UpdateData(FALSE);
}



void LEFT_OPTION::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CqiuDoc* pDoc = (CqiuDoc*)CFormView::GetDocument();
	UpdateData();

	pDoc->Dis = (FLOAT)cTranslateX.GetPos();
//	float aaaa = (FLOAT)cTranslateY.GetPos();
//	float ddddd = pDoc->Moon_R - (FLOAT)cTranslateY.GetPos();
	if((pDoc->Moon_R - (FLOAT)cTranslateY.GetPos() >0.0001)|| (pDoc->Moon_R - (FLOAT)cTranslateY.GetPos() <- 0.0001))
		pDoc->moon_change = true;
	if ((pDoc->earth_change - (FLOAT)cTranslateY.GetPos() > 0.0001)|| (pDoc->earth_change- (FLOAT)cTranslateY.GetPos() < -0.0001))
		pDoc->earth_change = true;
	pDoc->Moon_R = (FLOAT)cTranslateY.GetPos();
	pDoc->Earth_R = (FLOAT)cTranslateZ.GetPos();
	pDoc->RotateX = (FLOAT)(cRotateX.GetPos()*0.1);
	pDoc->RotateY = (FLOAT)(cRotateY.GetPos()*0.1);
	pDoc->RotateZ = (FLOAT)(cRotateZ.GetPos()*0.1);


	UpdateData(FALSE);

	pDoc->UpdateAllViews(this);
	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);
}


void LEFT_OPTION::OnBnClickedPattern1()
{
	// TODO: 在此添加控件通知处理程序代码
	CqiuDoc* pDoc = (CqiuDoc*)CFormView::GetDocument();
	pDoc->Pattern = 0;
	pDoc->UpdateAllViews(this);

}


void LEFT_OPTION::OnBnClickedPattern2()
{
	// TODO: 在此添加控件通知处理程序代码
	CqiuDoc* pDoc = (CqiuDoc*)CFormView::GetDocument();
	pDoc->Pattern = 1;
	pDoc->UpdateAllViews(this);
}



int LEFT_OPTION::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetTimer(0, 30, NULL);
	// TODO:  在此添加您专用的创建代码

	return 0;
}


void LEFT_OPTION::OnBnClickedLighting1()
{
	CqiuDoc* pDoc = (CqiuDoc*)CFormView::GetDocument();
	pDoc->lighting = 0;
	pDoc->UpdateAllViews(this);
	// TODO: 在此添加控件通知处理程序代码
}


void LEFT_OPTION::OnBnClickedLighting2()
{
	CqiuDoc* pDoc = (CqiuDoc*)CFormView::GetDocument();
	pDoc->lighting = 1;
	pDoc->UpdateAllViews(this);
	// TODO: 在此添加控件通知处理程序代码
}
