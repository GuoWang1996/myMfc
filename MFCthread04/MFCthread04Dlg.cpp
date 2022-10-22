
// MFCthread04Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCthread04.h"
#include "MFCthread04Dlg.h"
#include "afxdialogex.h"
#include "Psapi.h"
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


// CMFCthread04Dlg 对话框



CMFCthread04Dlg::CMFCthread04Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTHREAD04_DIALOG, pParent)
	, m_editPid(_T(""))
	, m_pid(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCthread04Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_editPid);
	DDX_Control(pDX, IDC_LIST1, m_listModule);
	DDX_Text(pDX, IDC_EDIT2, m_pid);
}

BEGIN_MESSAGE_MAP(CMFCthread04Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCthread04Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCthread04Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCthread04Dlg 消息处理程序

BOOL CMFCthread04Dlg::OnInitDialog()
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

void CMFCthread04Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCthread04Dlg::OnPaint()
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
HCURSOR CMFCthread04Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCthread04Dlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	DWORD pid = atoi(m_editPid);
	//HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	HANDLE handle = GetCurrentProcess();
	if (handle)
	{
		MessageBox(_T("打开成功"));
	}

	HMODULE  module = GetModuleHandle(NULL);
	MODULEINFO mi = { 0 };
	GetModuleInformation(handle, module,&mi,sizeof(MODULEINFO));
	int i = 0;
	CloseHandle(handle);
}

//遍历模块按钮
void CMFCthread04Dlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	int pid=atoi(m_pid);
	vector<ModuleList> moduleLists;
	moduleLists.clear();
	m_listModule.ResetContent();
	getAllModule(pid, moduleLists);
	//界面显示
	for (size_t i = 0; i < moduleLists.size(); i++)
	{
		CString str;
		str.Format("模块名称:%s 模块首地址:%X 模块大小:%X", moduleLists[i].moduleName, moduleLists[i].moduleFirstAdress, moduleLists[i].moduleSize);
		m_listModule.AddString(str);
	}
	UpdateData(FALSE);
}

//遍历模块
BOOL CMFCthread04Dlg::getAllModule(int pid, vector<ModuleList>&moduleLists)
{
	ModuleList moduleList;
	HANDLE handle;
	//1.快照
	handle = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
	if (!handle)
	{
		MessageBox("失败");
		return FALSE;
	}
	MODULEENTRY32 me32;
	me32.dwSize = sizeof(MODULEENTRY32);
	if (!Module32First(handle, &me32))
	{
		CloseHandle(handle);     // Must clean up the snapshot object!
		return(FALSE);
	}
	if (Module32First(handle, &me32))
	{
		do 
		{
				moduleList.moduleFirstAdress = (DWORD)me32.hModule;
				moduleList.moduleName = me32.szModule;
				moduleList.moduleSize = me32.modBaseSize;
				moduleLists.push_back(moduleList);
			

		} while (Module32Next(handle, &me32));
	}
	CloseHandle(handle);
	return TRUE;
}
