// TimedMsgBoxDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TimedMsgBox.h"
#include "TimedMsgBoxDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int g_num = 10;
// CTimedMsgBoxDlg 对话框


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


// CTimedMsgBoxDlg 消息处理程序

BOOL CTimedMsgBoxDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE); // 设置大图标
	SetIcon(m_hIcon, FALSE); // 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTimedMsgBoxDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
		MessageBox(NULL, L"时间到", L"", 0);
		CloseThreadpoolTimer(pTimer);
	}
	else
	{
		CString strOuput;
		strOuput.Format(L"剩余%d秒", g_num);
		MessageBox(NULL, strOuput, L"", 0);
	}
}

PTP_TIMER lpTimer = NULL;

void CTimedMsgBoxDlg::OnBnClickedResponse()
{
	//创建定时响应的函数
	lpTimer =
		CreateThreadpoolTimer(MsgBoxTimeoutCallback, this, NULL);
	if (lpTimer == NULL)
	{
		this->MessageBox(L"初始化失败");
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
		this->MessageBox(L"计时取消");
		CloseThreadpoolTimer(lpTimer);
		lpTimer = NULL;
	}
}
