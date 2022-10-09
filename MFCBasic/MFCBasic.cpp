#include <afxwin.h>
class MFCBasic :public CFrameWnd
{


};
class MyWinApp:public CWinApp
{
public:
	MyWinApp() {
	};
	virtual BOOL InitInstance() {
		MFCBasic* pFrame=new MFCBasic;
		pFrame->Create(NULL,"MFCbase");
		m_pMainWnd = pFrame;
		pFrame->ShowWindow(SW_SHOW);
		pFrame->UpdateWindow();
		return TRUE;
	}

};

MyWinApp myWinApp;