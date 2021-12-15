
// qiu.h: qiu 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"       // 主符号


// CqiuApp:
// 有关此类的实现，请参阅 qiu.cpp
//

class CqiuApp : public CWinApp
{
public:
	CqiuApp() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	#ifdef _DEBUG
protected:
      CMemoryState m_msOld, m_msNew, m_msDiff;
#endif  // _DEBUG
// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CqiuApp theApp;
