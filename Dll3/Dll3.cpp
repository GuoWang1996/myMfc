// Dll3.cpp : 定义 DLL 的导出函数。
//

#include "pch.h"
#include "framework.h"
#include "Dll3.h"


// 这是导出变量的一个示例
DLL3_API int nDll3=0;

// 这是导出函数的一个示例。
DLL3_API int fnDll3(void)
{
    return 0;
}

// 这是已导出类的构造函数。
CDll3::CDll3()
{
    return;
}
