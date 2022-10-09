// MFC02_04.h: MFC02_04 DLL 的主标头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主符号


// CMFC0204App
// 有关此类实现的信息，请参阅 MFC02_04.cpp
//

class CMFC0204App : public CWinApp
{
public:
	CMFC0204App();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
