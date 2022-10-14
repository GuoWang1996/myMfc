#pragma once


// MChildTwoDiaLog 对话框

class MChildTwoDiaLog : public CDialogEx
{
	DECLARE_DYNAMIC(MChildTwoDiaLog)

public:
	MChildTwoDiaLog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MChildTwoDiaLog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
