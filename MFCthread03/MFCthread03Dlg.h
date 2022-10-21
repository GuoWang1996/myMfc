
// MFCthread03Dlg.h: 头文件
//

#pragma once
#include<vector>
using namespace std;

// CMFCthread03Dlg 对话框
class CMFCthread03Dlg : public CDialogEx
{
// 构造
public:
	CMFCthread03Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTHREAD03_DIALOG };
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
	afx_msg void OnBnClickedButton1();
	BOOL getAllProcess(vector<DWORD>&threadIds);
	CListBox m_listBox;
	CListCtrl m_listCtrl;
};
