#pragma once


// 非模态 对话框

class 非模态 : public CDialogEx
{
	DECLARE_DYNAMIC(非模态)

public:
	非模态(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~非模态();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnDestroy();
//	virtual void OnCancel();
	virtual void OnCancel();
	virtual void PostNcDestroy();
};
