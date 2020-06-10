// ShareSegmentDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ShareSegment.h"
#include "ShareSegmentDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  ID_TIMER 0
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV ֧��

	// ʵ��
protected:
DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CShareSegmentDlg �Ի���


CShareSegmentDlg::CShareSegmentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CShareSegmentDlg::IDD, pParent)
	  , m_uVal(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CShareSegmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_uVal);
	DDV_MinMaxUInt(pDX, m_uVal, 0, 9999);
}

CShareSegmentDlg::~CShareSegmentDlg()
{
	KillTimer(ID_TIMER);
}

BEGIN_MESSAGE_MAP(CShareSegmentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CShareSegmentDlg::OnBnClickedButton1)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CShareSegmentDlg ��Ϣ�������

BOOL CShareSegmentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE); // ���ô�ͼ��
	SetIcon(m_hIcon, FALSE); // ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//���ö�ʱ��
	SetTimer(ID_TIMER,500,0);
	return TRUE; // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CShareSegmentDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CShareSegmentDlg::OnPaint()
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
HCURSOR CShareSegmentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#pragma data_seg("Shared")
volatile LONG g_lApplicationInstances = 0;
#pragma data_seg()
//����һ�������
#pragma comment(linker, "/Section:Shared,RWS")

void CShareSegmentDlg::OnBnClickedButton1()
{
	UpdateData(true); //��ȡ����������
	this->m_uVal++;
	g_lApplicationInstances = this->m_uVal;
	UpdateData(false); //�����������
}


void CShareSegmentDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (!nIDEvent)
	{
		//����ʱ����Ϣ�ĺ���
		this->m_uVal = g_lApplicationInstances; //���ñ���
		UpdateData(false);
		CDialogEx::OnTimer(nIDEvent);
	}
}
