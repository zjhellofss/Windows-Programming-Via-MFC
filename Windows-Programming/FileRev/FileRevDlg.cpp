// FileRevDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileRev.h"
#include "FileRevDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFileRevDlg �Ի���


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


// CFileRevDlg ��Ϣ�������

BOOL CFileRevDlg::OnInitDialog()
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

void CFileRevDlg::OnPaint()
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
	 * �Զ�ռ�ķ�ʽ��һ���Ѿ����ڵ��ļ����򿪵�Ȩ��Ϊwrite��read
	 */
	HANDLE hFile = CreateFile(this->m_strFilePath, GENERIC_WRITE | GENERIC_READ, 0,
	                          NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		this->MessageBox(L"File open failed");
		this->m_btnOpen.EnableWindow(true);
		return;
	}
	//��ȡĿ���ļ��ĳߴ�
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	//�򿪹�����
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
		//����ͼ��дȨ��
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

		pchANSI = strstr(pchANSI, "\n\r"); // �ҵ���һ��\n\r��λ��

		while (pchANSI != NULL)
		{
			//�����滻
			*pchANSI++ = '\r';
			*pchANSI++ = '\n';
			pchANSI = strstr(pchANSI, "\n\r"); // �ҵ���һ��\r\n��λ��
		}

		// ������
		UnmapViewOfFile(pvFile);
		CloseHandle(hFileMap);

		// ����ĩ����'\0'
		SetFilePointer(hFile, dwFileSize, NULL, FILE_BEGIN);
		SetEndOfFile(hFile);
		CloseHandle(hFile);
		this->m_btnOpen.EnableWindow(true);
	}
}
