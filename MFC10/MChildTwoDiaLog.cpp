// MChildTwoDiaLog.cpp: 实现文件
//

#include "pch.h"
#include "MFC10.h"
#include "MChildTwoDiaLog.h"
#include "afxdialogex.h"


// MChildTwoDiaLog 对话框

IMPLEMENT_DYNAMIC(MChildTwoDiaLog, CDialogEx)

MChildTwoDiaLog::MChildTwoDiaLog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

MChildTwoDiaLog::~MChildTwoDiaLog()
{
}

void MChildTwoDiaLog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MChildTwoDiaLog, CDialogEx)
END_MESSAGE_MAP()


// MChildTwoDiaLog 消息处理程序


BOOL MChildTwoDiaLog::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_RETURN | pMsg->wParam == VK_ESCAPE))
	{
		return TRUE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
