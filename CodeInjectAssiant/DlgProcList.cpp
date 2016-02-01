// DlgProcList.cpp : implementation file
//

#include "stdafx.h"
#include "CodeInjectAssiant.h"
#include "DlgProcList.h"
#include "ntapi.h"

// CDlgProcList dialog

#define _get_proc_address(x,y,z) \
	x=(z##_ptr)GetProcAddress(y,#z);\
	if(x==NULL)\
	return 0; 

IMPLEMENT_DYNCREATE(CDlgProcList, CDialog)

CDlgProcList::CDlgProcList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProcList::IDD, pParent),ZwQuerySystemInformation(NULL)
{

}

CDlgProcList::~CDlgProcList()
{
}

void CDlgProcList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX,IDC_LT_PROCLIST,m_proclist);
}

BOOL CDlgProcList::OnInitDialog()
{
	CDialog::OnInitDialog();

	LV_COLUMN lvc;
	lvc.mask=LVCF_TEXT|LVCF_WIDTH;

	lvc.pszText="ProcessName";
	lvc.cx = 200;

	m_proclist.InsertColumn(0,&lvc);
	lvc.pszText="PID";
	lvc.cx = 60;
	m_proclist.InsertColumn(1,&lvc);

	m_proclist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_proclist.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	//初始化NativeAPI
	InitNativeAPI();
	m_processlists.clear();

	::CreateThread(NULL,0,GetProcLists_Thread,this,0,NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

BEGIN_MESSAGE_MAP(CDlgProcList, CDialog)
	ON_NOTIFY(NM_DBLCLK, IDC_LT_PROCLIST, &CDlgProcList::OnNMDblclkLtProclist)
END_MESSAGE_MAP()


//
void CDlgProcList::OnOK(){}
void CDlgProcList::OnCancel(){CDialog::OnCancel();}

int CDlgProcList::InitNativeAPI()
{
	HMODULE hNtdll=::GetModuleHandle("ntdll.dll");
	if(hNtdll==NULL){
		return 0;
	}

	_get_proc_address(ZwQuerySystemInformation,hNtdll,ZwQuerySystemInformation);
	_get_proc_address(ZwQueryInformationProcess,hNtdll,ZwQueryInformationProcess);
	return 1;
}

//获取进程列表

DWORD WINAPI CDlgProcList::GetProcLists_Thread(LPVOID lpvoid){
	CDlgProcList *pDlg=(CDlgProcList*)lpvoid;

	pDlg->EnumProc2List();

	return 0;
}

void CDlgProcList::FillRecord2List(const char * procname,DWORD pid)
{
	char buf[50]={0};
	int item=m_proclist.GetItemCount();

	_itoa_s(pid,buf,10);
	m_proclist.InsertItem(item,procname);
	m_proclist.SetItemText(item,1,buf);
}

//枚举进程函数
void CDlgProcList::EnumProc2List()
{
	if(ZwQuerySystemInformation!=NULL){
		// get default process heap handle
		HANDLE hHeap = GetProcessHeap();

		NTSTATUS Status;
		ULONG cbBuffer = 0x8000;
		PVOID pBuffer = NULL;

		// it is difficult to predict what buffer size will be
		// enough, so we start with 32K buffer and increase its
		// size as needed
		do
		{
			pBuffer = HeapAlloc(hHeap, 0, cbBuffer);
			if (pBuffer == NULL)
				return;

			Status = ZwQuerySystemInformation(
				SystemProcessesAndThreadsInformation,
				pBuffer, cbBuffer, NULL);

			if (Status == STATUS_INFO_LENGTH_MISMATCH)
			{
				HeapFree(hHeap, 0, pBuffer);
				cbBuffer *= 2;
			}
			else if (!NT_SUCCESS(Status))
			{
				HeapFree(hHeap, 0, pBuffer);
				return;
			}
		}
		while (Status == STATUS_INFO_LENGTH_MISMATCH);

		PSYSTEM_PROCESS_INFORMATION pProcesses = (PSYSTEM_PROCESS_INFORMATION)pBuffer;

		for (;;)
		{
			PCWSTR pszProcessName = pProcesses->ProcessName.Buffer;
			
			
			if (pszProcessName == NULL)
				pszProcessName = L"Idle";

			USES_CONVERSION;
			std::string strProcessName=W2A(pszProcessName);
			/*m_processlists.insert(std::make_pair(strProcessName,pProcesses->ProcessId));*/
			FillRecord2List(strProcessName.c_str(),pProcesses->ProcessId);
			if (pProcesses->NextEntryDelta == 0)
				break;

			// find the address of the next process structure
			pProcesses = (PSYSTEM_PROCESS_INFORMATION)(((LPBYTE)pProcesses)
				+ pProcesses->NextEntryDelta);
		}

		HeapFree(hHeap, 0, pBuffer);
	}


	//填充列表
	if(m_processlists.size()!=0){
		std::map<std::string,DWORD>::iterator iter;
		for(iter=m_processlists.begin();iter!=m_processlists.end();iter++){
		
			FillRecord2List(iter->first.c_str(),iter->second);
		}
	}
}

//双击
void CDlgProcList::OnNMDblclkLtProclist(NMHDR *pNMHDR, LRESULT *pResult)
{
	char buf[50];
	DWORD pid=0;
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	m_proclist.GetItemText(pNMItemActivate->iItem,1,buf,50);
	pid=atoi(buf);
	::SendMessageA(this->GetParent()->m_hWnd,WM_SENDPROCESSID,0,(LPARAM)pid);
	
	*pResult = 0;

	OnCancel();
}
