// MFC16.h: MFC16 DLL 的主标头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// 主符号


// CMFC16App
// 有关此类实现的信息，请参阅 MFC16.cpp
//

class CMFC16App : public CWinApp
{
public:
	CMFC16App();

// 重写
public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();

	DECLARE_MESSAGE_MAP()
};
