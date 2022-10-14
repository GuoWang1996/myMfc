#pragma once


// MChildDiaLog 对话框

class MChildDiaLog : public CDialogEx
{
	DECLARE_DYNAMIC(MChildDiaLog)

public:
	MChildDiaLog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MChildDiaLog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
