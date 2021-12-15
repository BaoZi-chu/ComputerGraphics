#pragma once



// LEFT_OPTION 窗体视图

class LEFT_OPTION : public CFormView
{
	DECLARE_DYNCREATE(LEFT_OPTION)

protected:
	LEFT_OPTION();           // 动态创建所使用的受保护的构造函数
	virtual ~LEFT_OPTION();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_LEFT_VIEW };

	//}}AFX_DATA
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
public:

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	virtual void OnInitialUpdate(); 

	CSliderCtrl cRotateX;
	CSliderCtrl cTranslateX;
	CSliderCtrl cRotateY;
	CSliderCtrl cTranslateY;
	CSliderCtrl cTranslateZ;
	CSliderCtrl cRotateZ;
	int nPattern;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedPattern1();
	afx_msg void OnBnClickedPattern2();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBnClickedLighting1();
	BOOL light;
	afx_msg void OnBnClickedLighting2();
};


