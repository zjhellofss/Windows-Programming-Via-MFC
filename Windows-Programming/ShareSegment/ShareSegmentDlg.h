
// ShareSegmentDlg.h : 头文件
//

#pragma once


// CShareSegmentDlg 对话框
class CShareSegmentDlg : public CDialogEx
{
// 构造
public:
	CShareSegmentDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SHARESEGMENT_DIALOG };
	~CShareSegmentDlg();

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
private:
	UINT m_uVal;
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
