
// MFC12Dlg.h: 头文件
//

#pragma once


// CMFC12Dlg 对话框
class CMFC12Dlg : public CDialogEx
{
// 构造
public:
	CMFC12Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC12_DIALOG };
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
	void PrintDirs();
	void Recurse(LPCTSTR pstr);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

	CString fileName;
};
