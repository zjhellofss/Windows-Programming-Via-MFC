
// TimedMsgBox.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTimedMsgBoxApp:
// �йش����ʵ�֣������ TimedMsgBox.cpp
//

class CTimedMsgBoxApp : public CWinApp
{
public:
	CTimedMsgBoxApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTimedMsgBoxApp theApp;