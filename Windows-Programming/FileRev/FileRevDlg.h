// FileRevDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CFileRevDlg �Ի���
class CFileRevDlg : public CDialogEx
{
	// ����
public:
	CFileRevDlg(CWnd* pParent = NULL); // ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_FILEREV_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV ֧��
private:
	CString m_strFilePath;
	CButton m_btnOpen;
	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedReverse();
	
};
