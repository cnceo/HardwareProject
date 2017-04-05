
// GMServerToolDlg.h : 头文件
//

#pragma once
enum DlgType
{
	LoginDlg_Type,
	CmdPage_Type,
};

class DlgLogin;
class DlgGMToolListPage;

// CGMServerToolDlg 对话框
class CGMServerToolDlg : public CDialogEx
{
// 构造
public:
	CGMServerToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GMSERVERTOOL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	std::map<DlgType, CDialogEx*> _dlgs;
	
	
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMove(int x, int y);
	DlgLogin* GetLogin();
	DlgGMToolListPage* GetGMTool();
	void LoginSucessful();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
