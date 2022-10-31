// MFC16.cpp: 定义 DLL 的初始化例程。
//

#include "pch.h"
#include "framework.h"
#include "MFC16.h"
#include "dllDialogMain.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define MYTHREAD(a,b,c,d,e,f)\
((HANDLE)_beginthreadex((void*)a,b,(_beginthreadex_proc_type)c,(void*)d,e,(unsigned int*)f))
//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CMFC16App

BEGIN_MESSAGE_MAP(CMFC16App, CWinApp)
END_MESSAGE_MAP()


// CMFC16App 构造

CMFC16App::CMFC16App()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CMFC16App 对象
void Call_输出调试信息(char*pszFormat, ...) {
#ifdef _DEBUG
	char szbufFormat[0x1000];
	char szbufFormat_Game[0x1000] = "";
	va_list argList;
	va_start(argList, pszFormat);//参数列表初始化
	vsprintf_s(szbufFormat, pszFormat, argList);
	strcat_s(szbufFormat_Game, szbufFormat);
	OutputDebugString(szbufFormat_Game);
	va_end(argList);
#endif
}
CMFC16App theApp;
DWORD WINAPI MyThreadFunction2(LPVOID lpParam) {
	Call_输出调试信息("hello:MyThreadFunction2\n");
	FreeLibraryAndExitThread(theApp.m_hInstance, 0);
	return -5;

}
DWORD WINAPI MyThreadFunction(LPVOID lpParam) {
	Call_输出调试信息("hello:MyThreadFunction\n");
	dllDialogMain dgm;
	dgm.DoModal();
	DWORD adress = 0;
	HANDLE handle = ::CreateThread(NULL, NULL, MyThreadFunction2, (LPVOID)2, 0, &adress);
	return -5;

}

// CMFC16App 初始化

BOOL CMFC16App::InitInstance()
{
	Call_输出调试信息("hello:InitInstance\n");
	CWinApp::InitInstance();
	DWORD adress = 0;
	HANDLE handle = MYTHREAD(NULL, NULL, MyThreadFunction, (LPVOID)2, 0, &adress);
	return TRUE;
}

BOOL CMFC16App::ExitInstance()
{
	Call_输出调试信息("hello:ExitInstance退出\n");
	return TRUE;
}
