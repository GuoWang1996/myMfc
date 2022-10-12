#pragma once


// 模态 对话框

class 模态 : public CDialogEx
{
	DECLARE_DYNAMIC(模态)

public:
	模态(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~模态();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
