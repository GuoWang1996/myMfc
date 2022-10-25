﻿
// MFCthread06Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCthread06.h"
#include "MFCthread06Dlg.h"
#include "afxdialogex.h"
#include<vector>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCthread06Dlg 对话框



CMFCthread06Dlg::CMFCthread06Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTHREAD06_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCthread06Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listWindnowHwnd);
}

BEGIN_MESSAGE_MAP(CMFCthread06Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCthread06Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCthread06Dlg 消息处理程序

BOOL CMFCthread06Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCthread06Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCthread06Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCthread06Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//判断窗口是否可见
BOOL isWindowsRange(HWND hwnd)
{
	return (GetWindow(hwnd, GW_OWNER) == NULL && IsWindowVisible(hwnd));
}
typedef struct INFO
{
	CString text;
	DWORD pid;
	HWND hwnd;
}INFO;
static HWND g_hwnd;
static 	vector<INFO> windowLists;
void CMFCthread06Dlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	m_listWindnowHwnd.ResetContent();
	windowLists.clear();
	listWindowsHwnd(0);
	for (int i=0;i< windowLists.size();i++)
	{
		CString str;
		str.Format("窗口句柄:%X;窗口pid:%d;窗口标题:%s", windowLists[i].hwnd, windowLists[i].pid, windowLists[i].text);
		m_listWindnowHwnd.AddString(str);
	}
	UpdateData(FALSE);
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	TCHAR caption[200];

	memset(caption, 0, sizeof(caption));
	DWORD p_pid = lParam;
	if (p_pid!=0)
	{
		GetWindowThreadProcessId(hwnd, &p_pid);
		::GetWindowText(hwnd, caption, 200);
		return FALSE;
	}
	//如果窗口不可见,遍历下一个窗口
	if (!IsWindowVisible(hwnd))
	{
		return TRUE;
	}
	INFO info;
	GetWindowThreadProcessId(hwnd, &p_pid);
	::GetWindowText(hwnd, caption, 200);
	info.hwnd = hwnd;
	info.pid = p_pid;
	info.text = caption;
	windowLists.push_back(info);
	return TRUE;
}
//遍历窗口句柄
HWND CMFCthread06Dlg::listWindowsHwnd(DWORD pid)
{

	::EnumWindows(EnumWindowsProc, pid);
	return g_hwnd;
}

