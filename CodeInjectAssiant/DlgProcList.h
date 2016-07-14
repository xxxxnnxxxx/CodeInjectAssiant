#ifndef _DLGPROCLIST_H_
#define _DLGPROCLIST_H_

#include <Windows.h>
#include <map>
#include <string>
#include "ntapi.h"


class CDlgProcList : public CDialog
{
	DECLARE_DYNCREATE(CDlgProcList)

public:
	CDlgProcList(CWnd* pParent = NULL);
	virtual ~CDlgProcList();
	void OnOK();
	void OnCancel();
	enum { IDD = IDD_DLG_PROCLIST };
private:
    int InitNativeAPI();
protected:
	virtual void            DoDataExchange(CDataExchange* pDX);
	virtual BOOL            OnInitDialog();
	void                    FillRecord2List(const char * procname,DWORD pid);
	static  DWORD WINAPI    GetProcLists_Thread(LPVOID lpvoid);
	void EnumProc2List();
private:
	
	ZwQuerySystemInformation_ptr        ZwQuerySystemInformation;
	ZwQueryInformationProcess_ptr       ZwQueryInformationProcess;
    CListCtrl                           m_proclist;
    std::map<std::string,unsigned long> m_processlists;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMDblclkLtProclist(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnNMRClickLtProclist(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnRefreshList();   //刷新进程列表
};


#endif