// FileRevDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "FileRev.h"
#include "FileRevDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileRevDlg 对话框


CFileRevDlg::CFileRevDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFileRevDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileRevDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPEN, m_btnOpen);
}

BEGIN_MESSAGE_MAP(CFileRevDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &CFileRevDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_Reverse, &CFileRevDlg::OnBnClickedReverse)
END_MESSAGE_MAP()


// CFileRevDlg 消息处理程序

BOOL CFileRevDlg::OnInitDialog()
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

void CFileRevDlg::OnPaint()
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
HCURSOR CFileRevDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFileRevDlg::OnBnClickedOpen()
{
	CString strFile = _T("");

	CFileDialog dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Text Files (*.txt)|*.txt|All Files (*.*)|*.*||"),
	                    NULL);
	if (dlgFile.DoModal())
	{
		strFile = dlgFile.GetPathName();
		this->m_strFilePath = strFile;
		this->m_btnOpen.EnableWindow(false);
	}
}


void CFileRevDlg::OnBnClickedReverse()
{
	if (this->m_strFilePath.IsEmpty())
	{
		this->m_btnOpen.EnableWindow(true);
		return;
	}
	/**
	 * 以独占的方式打开一个已经存在的文件，打开的权限为write和read
	 */
	HANDLE hFile = CreateFile(this->m_strFilePath, GENERIC_WRITE | GENERIC_READ, 0,
	                          NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		this->MessageBox(L"File open failed");
		this->m_btnOpen.EnableWindow(true);
		return;
	}
	//获取目标文件的尺寸
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	//打开共享区
	HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE,
	                                    0, dwFileSize + sizeof(WCHAR), NULL);
	if (hFileMap == NULL)
	{
		this->MessageBox(L"File map could not be opened.");
		CloseHandle(hFile);
		this->m_btnOpen.EnableWindow(true);
		return;
	}
	else
	{
		//对视图的写权限
		PVOID pvFile = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);

		if (pvFile == NULL)
		{
			this->MessageBox(L"Could not map view of file.");
			CloseHandle(hFileMap);
			CloseHandle(hFile);
			this->m_btnOpen.EnableWindow(true);
			return;
		}
		PSTR pchANSI = (PSTR)pvFile;
		pchANSI[dwFileSize / sizeof(CHAR)] = 0;
		_strrev(pchANSI);

		pchANSI = strstr(pchANSI, "\n\r"); // 找到第一个\n\r的位置

		while (pchANSI != NULL)
		{
			//进行替换
			*pchANSI++ = '\r';
			*pchANSI++ = '\n';
			pchANSI = strstr(pchANSI, "\n\r"); // 找到下一个\r\n的位置
		}

		// 清楚句柄
		UnmapViewOfFile(pvFile);
		CloseHandle(hFileMap);

		// 在文末设置'\0'
		SetFilePointer(hFile, dwFileSize, NULL, FILE_BEGIN);
		SetEndOfFile(hFile);
		CloseHandle(hFile);
		this->m_btnOpen.EnableWindow(true);
	}
}
