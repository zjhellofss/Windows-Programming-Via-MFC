
// TimedMsgBoxDlg.h : ͷ�ļ�
//

#pragma once


// CTimedMsgBoxDlg �Ի���
class CTimedMsgBoxDlg : public CDialogEx
{
// ����
public:
	CTimedMsgBoxDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TIMEDMSGBOX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedResponse();
	afx_msg void OnBnClickedCancel();
};
