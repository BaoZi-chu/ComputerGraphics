
// PolygonFillView.cpp: CPolygonFillView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "PolygonFill.h"
#endif

#include "PolygonFillDoc.h"
#include "PolygonFillView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPolygonFillView

IMPLEMENT_DYNCREATE(CPolygonFillView, CView)

BEGIN_MESSAGE_MAP(CPolygonFillView, CView)
END_MESSAGE_MAP()

// CPolygonFillView 构造/析构

CPolygonFillView::CPolygonFillView() noexcept
{
	// TODO: 在此处添加构造代码
	hex.ReadPoint();

}

CPolygonFillView::~CPolygonFillView()
{
}

BOOL CPolygonFillView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPolygonFillView 绘图

void CPolygonFillView::DrawGraph()
{
	CRect rect;                                         //定义客户区
	GetClientRect(&rect);                               //获得客户区的大小
	CDC* pDC = GetDC();                                   //定义设备上下文指针              
	pDC->SetMapMode(MM_ANISOTROPIC);                    //自定义坐标系
	pDC->SetWindowExt(rect.Width(), rect.Height());      //设置窗口比例
	pDC->SetViewportExt(rect.Width(), -rect.Height());   //设置视区比例，且x轴水平向右，y轴垂直向上
	pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);//设置客户区中心为坐标系原点
	rect.OffsetRect(-rect.Width() / 2, -rect.Height() / 2);  //矩形与客户区重合
	hex.DrawPolygon(pDC);//绘制多边形
	hex.FillPolygon(pDC);//填充多边形
	ReleaseDC(pDC);//释放DC
}

void CPolygonFillView::OnDraw(CDC* /*pDC*/)
{
	CPolygonFillDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	DrawGraph();
	// TODO: 在此处为本机数据添加绘制代码
}


// CPolygonFillView 诊断

#ifdef _DEBUG
void CPolygonFillView::AssertValid() const
{
	CView::AssertValid();
}

void CPolygonFillView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPolygonFillDoc* CPolygonFillView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPolygonFillDoc)));
	return (CPolygonFillDoc*)m_pDocument;
}
#endif //_DEBUG


// CPolygonFillView 消息处理程序
