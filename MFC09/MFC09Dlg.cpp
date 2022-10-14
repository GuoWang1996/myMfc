
// MFC09Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFC09.h"
#include "MFC09Dlg.h"
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


// CMFC09Dlg 对话框



CMFC09Dlg::CMFC09Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC09_DIALOG, pParent)
	, m_account(_T(""))
	, m_password(_T(""))
	, m_adress(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC09Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_account);
	DDX_Text(pDX, IDC_EDIT2, m_password);
	DDX_Text(pDX, IDC_EDIT3, m_adress);
}

BEGIN_MESSAGE_MAP(CMFC09Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFC09Dlg::OnBnClickedButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CMFC09Dlg::OnNMClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CMFC09Dlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CMFC09Dlg 消息处理程序

BOOL CMFC09Dlg::OnInitDialog()
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
	( LVS_EX_GRIDLINES| LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES);
	m_listCtrl.InsertColumn(0,"账号", LVCFMT_CENTER,100);
	m_listCtrl.InsertColumn(1, "密码", LVCFMT_CENTER, 100);
	CRect crect;
	m_listCtrl.GetClientRect(&crect);
	int nWidth = crect.Width()- m_listCtrl.GetColumnWidth(0) - m_listCtrl.GetColumnWidth(1);
	m_listCtrl.InsertColumn(2, "区服", LVCFMT_CENTER, nWidth);
	//插入行数据

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFC09Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC09Dlg::OnPaint()
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
HCURSOR CMFC09Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFC09Dlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	int count=m_listCtrl.GetItemCount();
	m_listCtrl.InsertItem(count, m_account);
	m_listCtrl.SetItemText(count, 1, m_password);
	m_listCtrl.SetItemText(count, 2, m_adress);
	UpdateData(FALSE);
}

//单击事件
void CMFC09Dlg::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);//自动生成
	// TODO: 在此添加控件通知处理程序代码
	int i=pNMItemActivate->iItem;
	CString account =m_listCtrl.GetItemText(i, 0);
	CString passWord = m_listCtrl.GetItemText(i, 1);
	CString adress = m_listCtrl.GetItemText(i, 2);
	*pResult = 0;//自动生成
}

//双击事件删除
void CMFC09Dlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int i = pNMItemActivate->iItem;
	BOOL b= m_listCtrl.GetCheck(i);
	m_listCtrl.DeleteItem(i);
	*pResult = 0;
}
