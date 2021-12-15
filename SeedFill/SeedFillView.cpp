
// SeedFillView.cpp: CSeedFillView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SeedFill.h"
#endif

#include "SeedFillDoc.h"
#include "SeedFillView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSeedFillView

IMPLEMENT_DYNCREATE(CSeedFillView, CView)

BEGIN_MESSAGE_MAP(CSeedFillView, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CSeedFillView 构造/析构

CSeedFillView::CSeedFillView() noexcept
{
	SeedClr = RGB(255, 0, 0);//种子颜色
	BoundaryClr = RGB(0, 0, 0);//边界颜色
	BkClr = RGB(255, 200, 0);//背景颜色
	// TODO: 在此处添加构造代码

}

CSeedFillView::~CSeedFillView()
{
}

void CSeedFillView::OnDraw(CDC* pDC)
{
	CSeedFillDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	DoubleBuffer(pDC);
	// TODO: 在此处为本机数据添加绘制代码
}

BOOL CSeedFillView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CSeedFillView 绘图

void CSeedFillView::DoubleBuffer(CDC* pDC)
{
	CRect rect;//定义客户区
	GetClientRect(&rect);//获得客户区的大小
	nClientWidth = rect.Width();//屏幕客户区宽度
	nClientHeight = rect.Height();//屏幕客户区高度
	nHWidth = nClientWidth / 2;//屏幕客户区半宽
	nHHeight = nClientHeight / 2;//屏幕客户区半高
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap NewBitmap, * pOldBitmap;
	NewBitmap.LoadBitmap(IDB_BITMAP2);
	pOldBitmap = memDC.SelectObject(&NewBitmap);
	BITMAP bmp;
	NewBitmap.GetBitmap(&bmp);
	int nX = rect.left + (nClientWidth - bmp.bmWidth) / 2;//计算位图在客户区的中心点
	int nY = rect.top + (nClientHeight - bmp.bmHeight) / 2;
	pDC->BitBlt(nX, nY, nClientWidth, nClientHeight, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pOldBitmap);
	NewBitmap.DeleteObject();
}

void CSeedFillView::BoundaryFill()
{
	CDC* pDC = GetDC();
	pHead = new CStackNode;	//建立栈头结点
	pHead->pNext = NULL;	//栈头结点的指针域为空
	Push(Seed);				//种子像素入栈
	if (BkClr != pDC->GetPixel(Seed.x, Seed.y) && BoundaryClr != pDC->GetPixel(Seed.x, Seed.y))
	{
		while (NULL != pHead->pNext)//如果栈不为空
		{
			CPoint PopPoint;
			Pop(PopPoint);
			if (SeedClr == pDC->GetPixel(PopPoint.x, PopPoint.y))
				continue;//加速处理
			pDC->SetPixelV(PopPoint.x, PopPoint.y, SeedClr);
			Left.x = PopPoint.x - 1;//搜索出栈结点的左方像素
			Left.y = PopPoint.y;
			COLORREF CurPixClr;		//当前像素的颜色
			CurPixClr = pDC->GetPixel(Left.x, Left.y);
			if (BoundaryClr != CurPixClr && SeedClr != CurPixClr)	//不是边界色并且未置成填充色
				Push(Left);//左方像素入栈
			Top.x = PopPoint.x;//搜索出栈结点的上方像素
			Top.y = PopPoint.y + 1;
			CurPixClr = pDC->GetPixel(Top.x, Top.y);
			if (BoundaryClr != CurPixClr && SeedClr != CurPixClr)
				Push(Top);//上方像素入栈
			Right.x = PopPoint.x + 1;//搜索出栈结点的右方像素
			Right.y = PopPoint.y;
			CurPixClr = pDC->GetPixel(Right.x, Right.y);
			if (BoundaryClr != CurPixClr && SeedClr != CurPixClr)
				Push(Right);//右方像素入栈
			Bottom.x = PopPoint.x;//搜索出栈结点的下方像素
			Bottom.y = PopPoint.y - 1;
			CurPixClr = pDC->GetPixel(Bottom.x, Bottom.y);
			if (BoundaryClr != CurPixClr && SeedClr != CurPixClr)
				Push(Bottom);//下方像素如栈
		}
	}
	else
		MessageBox(_T("请在空心字体内部单击鼠标左键!"), _T("提示"));
	delete pHead;
	pHead = NULL;
	ReleaseDC(pDC);
}

void CSeedFillView::Push(CPoint point)
{
	pTop = new CStackNode;
	pTop->PixelPoint = point;
	pTop->pNext = pHead->pNext;
	pHead->pNext = pTop;
}

void CSeedFillView::Pop(CPoint& point)
{
	if (pHead->pNext != NULL)
	{
		pTop = pHead->pNext;
		pHead->pNext = pTop->pNext;
		point = pTop->PixelPoint;
		delete pTop;
	}
}



// CSeedFillView 诊断

#ifdef _DEBUG
void CSeedFillView::AssertValid() const
{
	CView::AssertValid();
}

void CSeedFillView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSeedFillDoc* CSeedFillView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSeedFillDoc)));
	return (CSeedFillDoc*)m_pDocument;
}
#endif //_DEBUG


// CSeedFillView 消息处理程序


void CSeedFillView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Seed = point;//选择种子位置
	BoundaryFill();//填充图形
	CView::OnLButtonDown(nFlags, point);
}
