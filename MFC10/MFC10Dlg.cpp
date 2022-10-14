
// MFC10Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC10.h"
#include "MFC10Dlg.h"
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


// CMFC10Dlg 对话框



CMFC10Dlg::CMFC10Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC10_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabList);
}

BEGIN_MESSAGE_MAP(CMFC10Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMFC10Dlg::OnTcnSelchangeTab1)
END_MESSAGE_MAP()


// CMFC10Dlg 消息处理程序

BOOL CMFC10Dlg::OnInitDialog()
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
	m_tabList.InsertItem(0,"测试1");
	m_tabList.InsertItem(1, "测试2");
	m_tabList.InsertItem(2, "测试3");
	//获取大小 
	CRect crect;
	m_tabList.GetWindowRect(&crect);
	ScreenToClient(crect);
	CRect crect2;
	m_tabList.GetItemRect(0,&crect2);
	crect.top += crect2.Height();
	//创建子页面
	m_childOne.Create(IDD_DIALOG1,this);
	m_childTwo.Create(IDD_DIALOG2, this);
	//移动
	m_childOne.MoveWindow(&crect);
	m_childTwo.MoveWindow(&crect);
	//m_childOne->Create(IDD_DIALOG1, this);
	//设置默认显示页面
	m_tabList.SetCurSel(0);
	//显示
	m_childOne.ShowWindow(SW_SHOW);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC10Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC10Dlg::OnPaint()
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
HCURSOR CMFC10Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC10Dlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	int i=m_tabList.GetCurSel();
	switch (i)
	{
	case 0:
		m_childOne.ShowWindow(SW_SHOW);
		m_childTwo.ShowWindow(SW_HIDE);
		break;
	case 1:
		m_childOne.ShowWindow(SW_HIDE);
		m_childTwo.ShowWindow(SW_SHOW);
		break;
	}
	*pResult = 0;
}


BOOL CMFC10Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message==WM_KEYDOWN&&(pMsg->wParam==VK_RETURN| pMsg->wParam == VK_ESCAPE))
	{
		return TRUE;
	} 
	return CDialogEx::PreTranslateMessage(pMsg);
}
