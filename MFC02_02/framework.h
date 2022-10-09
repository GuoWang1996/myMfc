#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 部分 CString 构造函数将是显式的
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // 移除对话框中的 MFC 控件支持

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头文件中排除极少使用的内容
#endif

#include <afx.h>
#include <afxwin.h>         // MFC 核心组件和标准组件
