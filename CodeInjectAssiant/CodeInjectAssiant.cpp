
// CodeInjectAssiant.cpp : ����Ӧ�ó��������Ϊ��
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


// CCodeInjectAssiantApp ����

CCodeInjectAssiantApp::CCodeInjectAssiantApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CCodeInjectAssiantApp ����

CCodeInjectAssiantApp theApp;


// CCodeInjectAssiantApp ��ʼ��

static char g_SE[4][50]={"SeShutdownPrivilege",
"SeRestorePrivilege",
"SeBackupPrivilege",
"SeDebugPrivilege"};

unsigned long SetPrivilege(
				HANDLE hToken,          // access token handle
				LPCTSTR lpszPrivilege,  // name of privilege to enable/disable
				BOOL bEnablePrivilege   // to enable or disable privilege
				) 
{
	TOKEN_PRIVILEGES tp;
	LUID luid;

	if ( !LookupPrivilegeValueA( 
		NULL,            // lookup privilege on local system
		lpszPrivilege,   // privilege to lookup 
		&luid ) )        // receives LUID of privilege
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

	// Enable the privilege or disable all privileges.

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
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	EnableDebugPrivilege(TRUE);

	CCodeInjectAssiantDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
