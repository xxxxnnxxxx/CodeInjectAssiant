#ifndef _CODEINJECTASSIANT_H_
#define _CODEINJECTASSIANT_H_

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"


class CCodeInjectAssiantApp : public CWinAppEx
{
public:
	CCodeInjectAssiantApp();

	public:
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};

extern CCodeInjectAssiantApp theApp;

#endif