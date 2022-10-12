// 模态.cpp: 实现文件
//

#include "pch.h"
#include "MFC05.h"
#include "模态.h"
#include "afxdialogex.h"


// 模态 对话框

IMPLEMENT_DYNAMIC(模态, CDialogEx)

模态::模态(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

模态::~模态()
{
}

void 模态::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(模态, CDialogEx)
END_MESSAGE_MAP()


// 模态 消息处理程序
