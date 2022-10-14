// MChildDiaLog.cpp: 实现文件
//

#include "pch.h"
#include "MFC10.h"
#include "MChildDiaLog.h"
#include "afxdialogex.h"


// MChildDiaLog 对话框

IMPLEMENT_DYNAMIC(MChildDiaLog, CDialogEx)

MChildDiaLog::MChildDiaLog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

MChildDiaLog::~MChildDiaLog()
{
}

void MChildDiaLog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MChildDiaLog, CDialogEx)
END_MESSAGE_MAP()


// MChildDiaLog 消息处理程序
