
// CodeInjectAssiant.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCodeInjectAssiantApp:
// �йش����ʵ�֣������ CodeInjectAssiant.cpp
//

class CCodeInjectAssiantApp : public CWinAppEx
{
public:
	CCodeInjectAssiantApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCodeInjectAssiantApp theApp;