
// MFCthread08Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCthread08.h"
#include "MFCthread08Dlg.h"
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


// CMFCthread08Dlg 对话框



CMFCthread08Dlg::CMFCthread08Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTHREAD08_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCthread08Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCthread08Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCthread08Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCthread08Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCthread08Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCthread08Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFCthread08Dlg 消息处理程序

BOOL CMFCthread08Dlg::OnInitDialog()
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

void CMFCthread08Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCthread08Dlg::OnPaint()
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
HCURSOR CMFCthread08Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void Call_输出调试信息(char*pszFormat, ...) {
#ifdef _DEBUG
	char szbufFormat[0x1000];
	char szbufFormat_Game[0x1000] = "";
	va_list argList;
	va_start(argList, pszFormat);//参数列表初始化
	vsprintf_s(szbufFormat, pszFormat, argList);
	strcat_s(szbufFormat_Game, szbufFormat);
	OutputDebugString(szbufFormat_Game);
	va_end(argList);
#endif
}
HANDLE h_event;
HANDLE h_eventTwo;
//打印线程
unsigned __stdcall MyThreadFunction(void*  lpParam) {
	int value = 0;
	while (1)
	{

		WaitForSingleObject(h_event, INFINITE);
		ResetEvent(h_event);//关闭信号
		Call_输出调试信息("线程运行中----%d\n", value);
		value++;
	}
	int i = GetLastError();
	return -5;

}
//控制线程
unsigned __stdcall MyThreadFunction2(void*  lpParam) {
	while (1)
	{
		Sleep(1000);
		SetEvent(h_event);//开启信号
;
	}
	return -5;

}

//打印线程2
unsigned __stdcall MyThreadFunction3(void*  lpParam) {
	Call_输出调试信息("进入线程2----------\n");
	WaitForSingleObject(h_eventTwo, INFINITE);//事件2默认有信号，必然快速进入循环
	//自动复位无信号
	while (1)
	{
	
		if (WaitForSingleObject(h_eventTwo,20)== WAIT_OBJECT_0)	//如果有信号 
		{
			Call_输出调试信息("退出线程2----------\n");
			return 0;
		}
		//无信号
		Call_输出调试信息("线程执行中-------------\n");
		Sleep(1000);
	}
	return -5;

}
void CMFCthread08Dlg::OnBnClickedButton1()
{
	h_event=::CreateEvent(NULL,TRUE,FALSE,NULL);
	unsigned int adress = 0;
	HANDLE handele[2] = { 0 };
	handele[0]=(HANDLE)_beginthreadex(NULL, NULL, MyThreadFunction, NULL, 0, &adress);
	if (handele[0]==NULL)
	{
		MessageBox("线程1创建失败");
	}
	handele[1] = (HANDLE)_beginthreadex(NULL, NULL, MyThreadFunction2, NULL, 0, &adress);
	if (handele[1] == NULL)
	{
		MessageBox("线程2创建失败");
	}

	WaitForSingleObject(handele[0], INFINITE);
	CloseHandle(handele[0]);
	CloseHandle(handele[1]);
	CloseHandle(h_event);
}


void CMFCthread08Dlg::OnBnClickedButton2()
{
	h_eventTwo = ::CreateEvent(NULL, FALSE, TRUE, NULL);
	unsigned int adress = 0;
	HANDLE handele[2] = { 0 };
	handele[0] = (HANDLE)_beginthreadex(NULL, NULL, MyThreadFunction3, NULL, 0, &adress);
	if (handele[0] == NULL)
	{
		MessageBox("线程1创建失败");
	}


}

//开启信号
void CMFCthread08Dlg::OnBnClickedButton3()
{
	SetEvent(h_eventTwo);
}

//关闭信号
void CMFCthread08Dlg::OnBnClickedButton4()
{
	ResetEvent(h_eventTwo);
}
