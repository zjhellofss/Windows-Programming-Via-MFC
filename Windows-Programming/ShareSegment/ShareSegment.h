
// ShareSegment.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CShareSegmentApp:
// �йش����ʵ�֣������ ShareSegment.cpp
//

class CShareSegmentApp : public CWinApp
{
public:
	CShareSegmentApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CShareSegmentApp theApp;