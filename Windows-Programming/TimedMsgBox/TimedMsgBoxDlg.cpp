// TimedMsgBoxDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TimedMsgBox.h"
#include "TimedMsgBoxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int g_num = 10;
// CTimedMsgBoxDlg �Ի���


CTimedMsgBoxDlg::CTimedMsgBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTimedMsgBoxDlg::IDD, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimedMsgBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTimedMsgBoxDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RESPONSE, &CTimedMsgBoxDlg::OnBnClickedResponse)
	ON_BN_CLICKED(IDC_CANCEL, &CTimedMsgBoxDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CTimedMsgBoxDlg ��Ϣ�������

BOOL CTimedMsgBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE); // ���ô�ͼ��
	SetIcon(m_hIcon, FALSE); // ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE; // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTimedMsgBoxDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTimedMsgBoxDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

VOID CALLBACK MsgBoxTimeoutCallback(
	PTP_CALLBACK_INSTANCE pInstance,
	PVOID pvContext,
	PTP_TIMER pTimer
)
{
	CTimedMsgBoxDlg* pDlg = static_cast<CTimedMsgBoxDlg*>(pvContext);
	if (!pDlg)
	{
		return;
	}
	pDlg->UpdateData(false);
	g_num--;
	if (g_num == 0)
	{
		MessageBox(NULL, L"ʱ�䵽", L"", 0);
		CloseThreadpoolTimer(pTimer);
	}
	else
	{
		CString strOuput;
		strOuput.Format(L"ʣ��%d��", g_num);
		MessageBox(NULL, strOuput, L"", 0);
	}
}

PTP_TIMER lpTimer = NULL;

void CTimedMsgBoxDlg::OnBnClickedResponse()
{
	//������ʱ��Ӧ�ĺ���
	lpTimer =
		CreateThreadpoolTimer(MsgBoxTimeoutCallback, this, NULL);
	if (lpTimer == NULL)
	{
		this->MessageBox(L"��ʼ��ʧ��");
	}
	else
	{
		ULARGE_INTEGER ulRelativeStartTime;
		ulRelativeStartTime.QuadPart = (LONGLONG)-(10000000); // start in 1 second
		FILETIME ftRelativeStartTime;
		ftRelativeStartTime.dwHighDateTime = ulRelativeStartTime.HighPart;
		ftRelativeStartTime.dwLowDateTime = ulRelativeStartTime.LowPart;
		SetThreadpoolTimer(
			lpTimer,
			&ftRelativeStartTime,
			2000, // Triggers every 1000 milliseconds
			0
		);
		this->MessageBox(L"You have 10 seconds to response");
	}
}


void CTimedMsgBoxDlg::OnBnClickedCancel()
{
	if (lpTimer != NULL)
	{
		this->MessageBox(L"��ʱȡ��");
		CloseThreadpoolTimer(lpTimer);
		lpTimer = NULL;
	}
}
