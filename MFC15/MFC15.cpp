// MFC15.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "windows.h"
//#include "../StaticLib1/test.h"
#include "../Dll1/test.h"
#pragma comment(lib,"../Debug/DLL1.lib")
using namespace std;
int main()
{
	int i=add(2,3);
	printf("静态库%d\n", i);
	HANDLE handle= OpenMutex(MUTEX_ALL_ACCESS, TRUE,(LPCWSTR)"singleOpen");
	//如果无进程打开，正常创建
	if (handle==NULL)
	{
		handle=CreateMutex(NULL,TRUE, (LPCWSTR)"singleOpen");
		if (handle==NULL)
		{
			printf("创建互斥体失败");
			return -1;
		}
	
	}
	//等待函数检查互斥量线程ID,如果为0(互斥量处于触发状态)，则置为1.因此等待函数在初次调用新创建的互斥体时，必然无需等待(因为处于有信号状态)
	while (WaitForSingleObject(handle, 100) == WAIT_TIMEOUT)
	{
		MessageBox(NULL,(LPCWSTR)"请勿多开", (LPCWSTR)"标题",MB_OK);
		return -2;
	}
	while (1)
	{
		//主程序自定义代码
		printf("程序运行中--------------\n");
		Sleep(1000);
	}
	ReleaseMutex(handle);
	CloseHandle(handle);
	handle = NULL;
	system("pause");
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
