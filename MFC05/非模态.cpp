// 非模态.cpp: 实现文件
//

#include "pch.h"
#include "MFC05.h"
#include "非模态.h"
#include "afxdialogex.h"
#include "MFC05Dlg.h"

// 非模态 对话框

IMPLEMENT_DYNAMIC(非模态, CDialogEx)

非模态::非模态(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

非模态::~非模态()
{
}

void 非模态::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(非模态, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// 非模态 消息处理程序


void 非模态::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}


void 非模态::OnDestroy()
{

	CDialogEx::OnDestroy();
	

	// TODO: 在此处添加消息处理程序代码
}



void 非模态::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnCancel();
	DestroyWindow();
}


void 非模态::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
	if (CMFC05Dlg::cmfc05Dlg)
	{
		CMFC05Dlg::cmfc05Dlg->noMt = NULL;
	}
	
	CDialogEx::PostNcDestroy();
}
