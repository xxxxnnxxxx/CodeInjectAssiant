
// CodeInjectAssiant.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "CodeInjectAssiant.h"
#include "CodeInjectAssiantDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCodeInjectAssiantApp

BEGIN_MESSAGE_MAP(CCodeInjectAssiantApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


CCodeInjectAssiantApp::CCodeInjectAssiantApp(){}

CCodeInjectAssiantApp theApp;


static char g_SE[4][50]={"SeShutdownPrivilege",
"SeRestorePrivilege",
"SeBackupPrivilege",
"SeDebugPrivilege"};

unsigned long SetPrivilege(
				HANDLE hToken,         
				LPCTSTR lpszPrivilege,
				BOOL bEnablePrivilege
				) 
{
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if ( !LookupPrivilegeValueA( 
		NULL,  
		lpszPrivilege,
		&luid ) )
	{
		printf("LookupPrivilegeValue error: %u\n", GetLastError() ); 
		return 0; 
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;
	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	if ( !AdjustTokenPrivileges(
		hToken, 
		0, 
		&tp, 
		sizeof(TOKEN_PRIVILEGES), 
		(PTOKEN_PRIVILEGES) NULL, 
		(PDWORD) NULL) )
	{ 
		printf("AdjustTokenPrivileges error: %u\n", GetLastError() ); 
		return 0; 
	} 

	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
	{
		printf("The token does not have the specified privilege. \n");
		return 0;
	} 

	return 1;
}

unsigned long EnableDebugPrivilege(unsigned long fEnable)
{
	HANDLE hToken;  
	unsigned long bRet=FALSE;
	int i=0;
	for( i=0;i<4;i++)
	{
		OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
		bRet=SetPrivilege(hToken,g_SE[i],fEnable);
		CloseHandle(hToken);
	}

	return bRet;
}

BOOL CCodeInjectAssiantApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	EnableDebugPrivilege(TRUE);

	CCodeInjectAssiantDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		
	}
	else if (nResponse == IDCANCEL)
	{
		
	}
	return FALSE;
}
