
// MFCthread07Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCthread07.h"
#include "MFCthread07Dlg.h"
#include "afxdialogex.h"
#include "mutex"
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


// CMFCthread07Dlg 对话框

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

CMFCthread07Dlg::CMFCthread07Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTHREAD07_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCthread07Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCthread07Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCthread07Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCthread07Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCthread07Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCthread07Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCthread07Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMFCthread07Dlg 消息处理程序

BOOL CMFCthread07Dlg::OnInitDialog()
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

void CMFCthread07Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCthread07Dlg::OnPaint()
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
HCURSOR CMFCthread07Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//临界区封装
class MyLock
{
public:
	MyLock(CRITICAL_SECTION* sct) :m_sct(sct)
	{
		if (m_sct ==NULL)return;
		EnterCriticalSection(m_sct);
		count++;
		
	};
	~MyLock() 
	{
		if (m_sct == NULL)return;
		while (count >0)
		{
			LeaveCriticalSection(m_sct);
			count--;
		}

	};
private:
	CRITICAL_SECTION* m_sct;
	int count;
};
class MyLock2
{
public:
	MyLock2();
	~MyLock2();

private:

};

CRITICAL_SECTION sct;
int index = 0;
mutex g_mutex;//互斥量
unsigned __stdcall MyBeginthreadex(void* lpParam) {
	for (int i=0;i<10000;i++)
	{
		Call_输出调试信息("加加原始值:%d\n", index);
		//EnterCriticalSection(&sct);
		//MyLock myLock(&sct);
		g_mutex.lock();
		++index;
		g_mutex.unlock();
		//LeaveCriticalSection(&sct);
		Call_输出调试信息("加加:%d\n", index);
	}
	return -5;
};
unsigned __stdcall MyBeginthreadex2(void* lpParam) {
	for (int i = 0; i < 10000; i++)
	{
		Call_输出调试信息("减减原始值:%d\n", index);
		//EnterCriticalSection(&sct);
		//MyLock myLock(&sct);
		g_mutex.lock();
		--index;
		g_mutex.unlock();
		//LeaveCriticalSection(&sct);
		Call_输出调试信息("减减:%d\n", index);
	}
	return -5;
};

void CMFCthread07Dlg::OnBnClickedButton1()
{
	//InitializeCriticalSection(&sct);
	unsigned int adress = 0;
	HANDLE h1 = (HANDLE)_beginthreadex(NULL, NULL, MyBeginthreadex, (VOID*)2, 0, &adress);
	HANDLE h2 = (HANDLE)_beginthreadex(NULL, NULL, MyBeginthreadex2, (VOID*)2, 0, &adress);
	WaitForSingleObject(h1, INFINITE);
	WaitForSingleObject(h2, INFINITE);
	CloseHandle(h1);
	CloseHandle(h2);
	Call_输出调试信息("index：----%d\n", index);
	//DeleteCriticalSection(&sct);
}

HANDLE handle[3] = { 0 };
void CMFCthread07Dlg::OnBnClickedButton2()
{

	handle[0] = ::OpenEvent(EVENT_MODIFY_STATE,FALSE, "h_eventTwo");
	handle[1] = ::OpenEvent(EVENT_MODIFY_STATE, FALSE, "h_eventEnd");
	handle[2] = ::OpenEvent(EVENT_MODIFY_STATE, FALSE, "h_eventRecovery");
	if (handle[0]==NULL)
	{
		MessageBox("获取权限失败");
	}
	else
	{
		MessageBox("获取权限成功");
	}
}

//暂停
void CMFCthread07Dlg::OnBnClickedButton3()
{
	SetEvent(handle[1]);
}


void CMFCthread07Dlg::OnBnClickedButton4()
{
	ResetEvent(handle[1]);
}


void CMFCthread07Dlg::OnBnClickedButton5()
{
	SetEvent(handle[0]);
}
