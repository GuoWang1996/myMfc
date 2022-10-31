// dllDialogMain.cpp: 实现文件
//

#include "pch.h"
#include "MFC16.h"
#include "dllDialogMain.h"
#include "afxdialogex.h"


// dllDialogMain 对话框

IMPLEMENT_DYNAMIC(dllDialogMain, CDialogEx)

dllDialogMain::dllDialogMain(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

dllDialogMain::~dllDialogMain()
{
}

void dllDialogMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(dllDialogMain, CDialogEx)
END_MESSAGE_MAP()


// dllDialogMain 消息处理程序
