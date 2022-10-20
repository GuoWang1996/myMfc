
// MFCthread01Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCthread01.h"
#include "MFCthread01Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define MYTHREAD(a,b,c,d,e,f)\
((HANDLE)_beginthreadex((void*)a,b,(_beginthreadex_proc_type)c,(void*)d,e,(unsigned int*)f))

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


// CMFCthread01Dlg 对话框



CMFCthread01Dlg::CMFCthread01Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTHREAD01_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCthread01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCthread01Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCthread01Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCthread01Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCthread01Dlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMFCthread01Dlg 消息处理程序

BOOL CMFCthread01Dlg::OnInitDialog()
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

void CMFCthread01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCthread01Dlg::OnPaint()
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
void Call_输出调试信息(char*pszFormat,...) {
#ifdef _DEBUG
	char szbufFormat[0x1000];
	char szbufFormat_Game[0x1000]="";
	va_list argList;
	va_start(argList, pszFormat);//参数列表初始化
	vsprintf_s(szbufFormat, pszFormat, argList);
	strcat_s(szbufFormat_Game, szbufFormat);
	OutputDebugString(szbufFormat_Game);
	va_end(argList);
#endif
}
//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCthread01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


DWORD WINAPI MyThreadFunction(LPVOID lpParam) {
	int value = (int)lpParam;
	//while (1)
	//{
	//	//TRACE("线程运行中----%d\n",lpParam2);
	//	Call_输出调试信息("线程运行中----%d\n", value);
	//	DWORD i = GetCurrentThreadId();
	//	Sleep(1000);
	//}
	DWORD threadId = GetCurrentThreadId();
	for (size_t i = 0; i < 10; i++)
	{
		Call_输出调试信息("线程运行中----%d,ID:%d\n", i, threadId);
		if (i==5)
		{
			ExitThread(threadId);
		}
		Sleep(1000);
	}
	int i=GetLastError();
	return -5;
	
}
unsigned __stdcall MyBeginthreadex(void* lpParam) {
	int value = (int)lpParam;
	while (1)
	{
		//TRACE("线程运行中----%d\n",lpParam2);
		Call_输出调试信息("_beginthreadex线程运行中----%d\n", value);
		DWORD i=GetCurrentThreadId();
		Sleep(1000);
	}
	int i = GetLastError();
	return -5;
};
static HANDLE g_handle;
void CMFCthread01Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	DWORD adress=0;
	//1.安全描述符 结构体 一般为NULL 默认值
	//2.堆栈大小 一般为NULL 默认值
	//3.线程函数地址 注意，这里是固定格式
	//4.线程参数
	//5.创建标志 可以CREATE_SUSPENDED 创建后挂起 or 0 立即执行
	//6.返回线程ID
	g_handle = MYTHREAD(NULL, NULL, MyThreadFunction, (LPVOID)2, 0,&adress);

	if (g_handle !=NULL)
	{
		MessageBox("创建线程成功@");
	}
	//关闭打开的对象句柄
	//CloseHandle()
	//WaitForSingleObject(g_handle, INFINITE);
}


void CMFCthread01Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned int adress = 0;
	g_handle =(HANDLE) _beginthreadex(NULL, NULL, MyBeginthreadex, (VOID*)2, 0, &adress);
	if (g_handle)
	{
		MessageBox("创建_beginthreadex线程成功@");
	}
}

//获取退出码
void CMFCthread01Dlg::OnBnClickedButton3()
{
	if (g_handle)
	{
		STILL_ACTIVE
		DWORD mode;
		int id=GetExitCodeThread(g_handle, &mode);
		Call_输出调试信息("线程退出码:----%d\n", mode);
	}
}
