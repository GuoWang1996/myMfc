
// MFC01.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主符号


// CMFC01App:
// 有关此类的实现，请参阅 MFC01.cpp
//

class CMFC01App : public CWinApp
{
public:
	CMFC01App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CMFC01App theApp;
