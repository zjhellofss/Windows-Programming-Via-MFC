// FileRevDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CFileRevDlg 对话框
class CFileRevDlg : public CDialogEx
{
	// 构造
public:
	CFileRevDlg(CWnd* pParent = NULL); // 标准构造函数

	// 对话框数据
	enum { IDD = IDD_FILEREV_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持
private:
	CString m_strFilePath;
	CButton m_btnOpen;
	// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedReverse();
	
};
