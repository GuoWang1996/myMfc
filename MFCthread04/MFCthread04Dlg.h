
// MFCthread04Dlg.h: 头文件
//

#pragma once
#include<vector>
using namespace std;

// CMFCthread04Dlg 对话框
class CMFCthread04Dlg : public CDialogEx
{
// 构造
public:
	CMFCthread04Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTHREAD04_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	typedef struct ModuleList
	{
		CString moduleName; //模块名称
		DWORD moduleFirstAdress;	//模块首地址
		DWORD moduleSize;	//模块大小
	}ModuleList;
public:
	CString m_editPid;
	afx_msg void OnBnClickedButton1();
	CListBox m_listModule;
	afx_msg void OnBnClickedButton2();
	BOOL getAllModule(int pid, vector<ModuleList>&moduleLists);
	CString m_pid;
	afx_msg void OnBnClickedButton3();
};
