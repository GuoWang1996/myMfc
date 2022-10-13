﻿
// MFC07Dlg.h: 头文件
//

#pragma once


// CMFC07Dlg 对话框
class CMFC07Dlg : public CDialogEx
{
// 构造
public:
	CMFC07Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC07_DIALOG };
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
	CEdit m_testEdit;
	afx_msg void OnBnClickedButton1();
	CString m_editStr;
	CButton m_testCheck;
//	BOOL m_testCheckBool;
};
