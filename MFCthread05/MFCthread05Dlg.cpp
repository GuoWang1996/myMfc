
// MFCthread05Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCthread05.h"
#include "MFCthread05Dlg.h"
#include "afxdialogex.h"

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


// CMFCthread05Dlg 对话框



CMFCthread05Dlg::CMFCthread05Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTHREAD05_DIALOG, pParent)
	, m_status(_T(""))
	, m_className(_T(""))
	, m_windowsName(_T(""))
	, m_handleName(_T(""))
	, m_editContext(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCthread05Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC1, m_status);
	DDX_Text(pDX, IDC_EDIT2, m_className);
	DDX_Text(pDX, IDC_EDIT1, m_windowsName);
	DDX_Text(pDX, IDC_EDIT3, m_handleName);
	DDX_Text(pDX, IDC_EDIT4, m_editContext);
}

BEGIN_MESSAGE_MAP(CMFCthread05Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCthread05Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCthread05Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCthread05Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFCthread05Dlg 消息处理程序

BOOL CMFCthread05Dlg::OnInitDialog()
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

void CMFCthread05Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCthread05Dlg::OnPaint()
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
HCURSOR CMFCthread05Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//获取句柄
void CMFCthread05Dlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	HWND hwnd = ::FindWindow(m_className.IsEmpty()?NULL: m_className.GetBuffer(),m_windowsName);
	int i = GetLastError();
	CString str;
	str.Format(_T("%X"),(DWORD)hwnd);
	m_handleName = str;
	UpdateData(FALSE);
}

//检测未响应
void CMFCthread05Dlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	//HWND hwnd=(HWND)atoi(m_handleName);
	HWND hwnd = ::FindWindow(m_className.IsEmpty() ? NULL : m_className.GetBuffer(), m_windowsName);
	if (::IsHungAppWindow(hwnd))
	{
		DWORD pid;
		GetWindowThreadProcessId(hwnd, &pid);
		HANDLE  handle=OpenProcess(PROCESS_ALL_ACCESS,FALSE,pid);
		TerminateProcess(handle, 666);
	}

}

//设置窗口内容
void CMFCthread05Dlg::OnBnClickedButton3()
{
	
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	HWND hwnd = ::FindWindow(m_className.IsEmpty() ? NULL : m_className.GetBuffer(), m_windowsName);
	::SetWindowText(hwnd,m_editContext);
}
