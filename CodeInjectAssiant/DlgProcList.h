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
	CDlgProcList(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgProcList();
	void OnOK();
	void OnCancel();
	enum { IDD = IDD_DLG_PROCLIST, IDH = IDR_HTML_DLGPROCLIST };
private:
	CListCtrl m_proclist;
	std::map<std::string,unsigned long> m_processlists;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	void    FillRecord2List(const char * procname,DWORD pid);
	static  DWORD WINAPI GetProcLists_Thread(LPVOID lpvoid);
	void EnumProc2List();
private:
	int InitNativeAPI();
	ZwQuerySystemInformation_ptr ZwQuerySystemInformation;
	ZwQueryInformationProcess_ptr ZwQueryInformationProcess;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMDblclkLtProclist(NMHDR *pNMHDR, LRESULT *pResult);

};


#endif