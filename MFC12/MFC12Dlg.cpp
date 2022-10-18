
// MFC12Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC12.h"
#include "MFC12Dlg.h"
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


// CMFC12Dlg 对话框



CMFC12Dlg::CMFC12Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC12_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC12Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC12Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC12Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFC12Dlg 消息处理程序

BOOL CMFC12Dlg::OnInitDialog()
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
	//可以通过构造函数或Open函数打开文件
	//但是构造函数打开文件失败 是以异常的形式表现错误
	//OPEN一般以返回值判断
	CFile file;
	//CFileException e;
	if (file.Open("text.txt", CFile::modeCreate| CFile::modeReadWrite))
	{
		//1.设置游标为初始位置
		file.SeekToBegin();
		//2.1 写入
		char name[] = "Hello World\n";
		file.Write(name, sizeof(name));//也可用strlen
		file.Write(name, sizeof(name));//也可用strlen
		file.Write(name, sizeof(name));//也可用strlen
		//file.Write(name, strlen(name));
		file.Flush();
		file.SeekToBegin();//游标重置
		//2.2 读
		char pbufRead[64] ; //初始化为0 否则没有\0
		file.Read(pbufRead, 64);
		CString cs= file.GetFilePath(); 
		CString fileName = file.GetFileName();
		CFileStatus status;
		file.GetStatus(status);
		//关闭流
		file.Close();
	}
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC12Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC12Dlg::OnPaint()
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
HCURSOR CMFC12Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC12Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog fileDialog(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,"MyType Files (*.txt)|*.txt|All Files (*.*)|*.*||",this);
	if (fileDialog.DoModal()== IDOK)
	{
		CString fileName = fileDialog.GetFileName();
		CString filePath = fileDialog.GetPathName();
		CFile file;
		if (file.Open(fileName, CFile::modeCreate | CFile::modeReadWrite))
		{
			//1.自定义文件处理
			//****************
			//2.关闭流
			file.Close();
		}
	}
}
