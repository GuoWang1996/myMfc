﻿// Dll1.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#define DLL1_EXPORTS
#include "Dll1.h"


// 这是导出变量的一个示例
int nDll1=0;

// 这是导出函数的一个示例。
 int  fnDll1(void)
{
    return 0;
}

// 这是已导出类的构造函数。
CDll1::CDll1()
{
	return;
}