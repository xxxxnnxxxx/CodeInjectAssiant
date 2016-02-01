
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


// CCodeInjectAssiantApp 构造

CCodeInjectAssiantApp::CCodeInjectAssiantApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CCodeInjectAssiantApp 对象

CCodeInjectAssiantApp theApp;


// CCodeInjectAssiantApp 初始化

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
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	EnableDebugPrivilege(TRUE);

	CCodeInjectAssiantDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}
