
// MFC02_Single.h: MFC02_Single 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // 主符号


// CMFC02SingleApp:
// 有关此类的实现，请参阅 MFC02_Single.cpp
//

class CMFC02SingleApp : public CWinApp
{
public:
	CMFC02SingleApp() noexcept;


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFC02SingleApp theApp;
