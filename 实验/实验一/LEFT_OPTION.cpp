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
	, nLighting(-1)
	, nPattern(-1)
	, nBlank(0)
{

}

LEFT_OPTION::~LEFT_OPTION()
{
}

void LEFT_OPTION::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_FACE, cCurFace);
	DDX_Control(pDX, IDC_SLIDER2, cRadius);
	DDX_Control(pDX, IDC_SLIDER3, cCount);
	DDX_Control(pDX, IDC_X_ROTA_SLIDER, cRotateX);
	DDX_Control(pDX, IDC_X_TRAN_SLIDER, cTranslateX);
	DDX_Control(pDX, IDC_Y_ROTA_SLIDER, cRotateY);
	DDX_Control(pDX, IDC_Y_TRAN_SLIDER, cTranslateY);
	DDX_Control(pDX, IDC_Z_TRAN_SLIDER, cTranslateZ);
	DDX_Control(pDX, IDC_Z_ROTA_SLIDER, cRotateZ);
	DDX_Radio(pDX, IDC_Lighting_1, nLighting);
	DDX_Radio(pDX, IDC_Pattern_1, nPattern);
	DDX_Radio(pDX, IDC_Blank_1, nBlank);
}

BEGIN_MESSAGE_MAP(LEFT_OPTION, CFormView)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_Pattern_1, &LEFT_OPTION::OnBnClickedPattern1)
	ON_BN_CLICKED(IDC_Pattern_2, &LEFT_OPTION::OnBnClickedPattern2)
	ON_BN_CLICKED(IDC_Lighting_1, &LEFT_OPTION::OnBnClickedLighting1)
	ON_BN_CLICKED(IDC_Lighting_2, &LEFT_OPTION::OnBnClickedLighting2)
	ON_BN_CLICKED(IDC_Blank_1, &LEFT_OPTION::OnBnClickedBlank1)
	ON_BN_CLICKED(IDC_Blank_2, &LEFT_OPTION::OnBnClickedBlank2)
	ON_WM_TIMER()
	ON_WM_CREATE()
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
	cRadius.SetRange(1, 20);
	cRadius.SetPos(10);
	cCount.SetRange(0, 7);
	cCount.SetPos(4);

	nPattern = 0;
	nLighting = 0;
	nBlank = 0;
	cTranslateX.SetRange(0, 10);
	cTranslateY.SetRange(0, 10);
	cTranslateZ.SetRange(0, 10);
	cTranslateX.SetPos(1);
	cTranslateY.SetPos(1);
	cTranslateZ.SetPos(1);
	cRotateX.SetRange(0, 10);
	cRotateY.SetRange(0, 10);
	cRotateZ.SetRange(0, 10);
	cRotateX.SetPos(1);
	cRotateY.SetPos(1);
	cRotateZ.SetPos(1);
	CString str("");
	str.Format(_T("当前球体面数为：%d"), (INT(8 * pow(4, cCount.GetPos()))));
	cCurFace.SetWindowTextW(str);
	//cCurFace.SetWindowText(str);
	UpdateData(FALSE);
}



void LEFT_OPTION::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CqiuDoc* pDoc = (CqiuDoc*)CFormView::GetDocument();
	UpdateData();

	pDoc->Radius = cRadius.GetPos();
	pDoc->Count = cCount.GetPos();
	pDoc->TranslateX = (FLOAT)(cTranslateX.GetPos() * 0.1);
	pDoc->TranslateY = (FLOAT)(cTranslateY.GetPos() * 0.1);
	pDoc->TranslateZ = (FLOAT)(cTranslateZ.GetPos() * 0.1);
	pDoc->RotateX = (FLOAT)cRotateX.GetPos();
	pDoc->RotateY = (FLOAT)cRotateY.GetPos();
	pDoc->RotateZ = (FLOAT)cRotateZ.GetPos();

	CString str("");
	str.Format(_T("当前球体面数为：%d"), (INT(8 * pow(4, cCount.GetPos()))));
	cCurFace.SetWindowTextW(str);

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



void LEFT_OPTION::OnBnClickedLighting1()
{
	// TODO: 在此添加控件通知处理程序代码
	CqiuDoc* pDoc = (CqiuDoc*)CFormView::GetDocument();
	pDoc->Lighting = 0;
	pDoc->UpdateAllViews(this);
}


void LEFT_OPTION::OnBnClickedLighting2()
{
	// TODO: 在此添加控件通知处理程序代码
	CqiuDoc* pDoc = (CqiuDoc*)CFormView::GetDocument();
	pDoc->Lighting = 1;
	pDoc->UpdateAllViews(this);
}


void LEFT_OPTION::OnBnClickedBlank1()
{
	// TODO: 在此添加控件通知处理程序代码
	CqiuDoc* pDoc = (CqiuDoc*)CFormView::GetDocument();
	pDoc->Blank = 0;
	pDoc->UpdateAllViews(this);
}


void LEFT_OPTION::OnBnClickedBlank2()
{
	// TODO: 在此添加控件通知处理程序代码
	CqiuDoc* pDoc = (CqiuDoc*)CFormView::GetDocument();
	pDoc->Blank = 1;
	pDoc->UpdateAllViews(this);
}


void LEFT_OPTION::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CqiuDoc* pDoc = (CqiuDoc*)CFormView::GetDocument();
	cRadius.SetPos(pDoc->Radius);
	CFormView::OnTimer(nIDEvent);
}


int LEFT_OPTION::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetTimer(0, 30, NULL);
	// TODO:  在此添加您专用的创建代码

	return 0;
}
