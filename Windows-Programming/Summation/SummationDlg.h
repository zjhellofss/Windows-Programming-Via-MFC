// SummationDlg.h : ͷ�ļ�
//

#pragma once


// CSummationDlg �Ի���
class CSummationDlg : public CDialogEx
{
	// ����
public:
	CSummationDlg(CWnd* pParent = NULL); // ��׼���캯��

	// �Ի�������
	enum { IDD = IDD_SUMMATION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV ֧��


	// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
DECLARE_MESSAGE_MAP()
public:
	int m_val;
	afx_msg void OnBnClickedOk();
};
