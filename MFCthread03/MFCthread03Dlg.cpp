
// MFCthread03Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCthread03.h"
#include "MFCthread03Dlg.h"
#include "afxdialogex.h"
#include "tlhelp32.h"
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


// CMFCthread03Dlg 对话框



CMFCthread03Dlg::CMFCthread03Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTHREAD03_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCthread03Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listBox);
	DDX_Control(pDX, IDC_LIST2, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CMFCthread03Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCthread03Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCthread03Dlg 消息处理程序

BOOL CMFCthread03Dlg::OnInitDialog()
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
	//初始化列
	m_listCtrl.SetExtendedStyle
	(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	m_listCtrl.InsertColumn(0, "账号", LVCFMT_CENTER, 100);
	m_listCtrl.InsertColumn(1, "密码", LVCFMT_CENTER, 100);
	CRect crect;
	m_listCtrl.GetClientRect(&crect);
	int nWidth = crect.Width() - m_listCtrl.GetColumnWidth(0) - m_listCtrl.GetColumnWidth(1);
	m_listCtrl.InsertColumn(2, "区服", LVCFMT_CENTER, nWidth);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCthread03Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCthread03Dlg::OnPaint()
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
HCURSOR CMFCthread03Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//遍历进程
void CMFCthread03Dlg::OnBnClickedButton1()
{
	vector<DWORD>threadIds;
	//刷新界面
	threadIds.clear();
	if (m_listBox.GetCount() > 0)
	{
		for (size_t i = m_listBox.GetCount(); i <= m_listBox.GetCount(); i--)
		{
			m_listBox.DeleteString(i);
		}

	}
	//获取所有进程ID
	getAllProcess(threadIds);
	//界面显示
	for (size_t i = 0; i < threadIds.size(); i++)
	{
		CString str;
		str.Format("%d", threadIds[i]);
		m_listBox.AddString(str);
	}
}

BOOL CMFCthread03Dlg::getAllProcess(vector<DWORD>&processIds)
{
	HANDLE handle;
	//1.快照
	handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!handle)
	{
		MessageBox("失败");
		return FALSE;
	}
	PROCESSENTRY32   pe = {0};	//大小一定要指定！！！
	pe.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(handle,&pe))
	{
		CloseHandle(handle);     // Must clean up the snapshot object!
		return(FALSE);
	}
	if (Process32First(handle, &pe))
	{
		 while (Process32Next(handle, &pe)) {
			processIds.push_back(pe.th32ProcessID);
		};
	}
	CloseHandle(handle);
	return TRUE;
}
