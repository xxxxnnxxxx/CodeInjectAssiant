
// CodeInjectAssiantDlg.h : 头文件
//

#pragma once

#include "hexeditctrl.h"
#include "MyPic.h"
#include "ntapi.h"


// CCodeInjectAssiantDlg 对话框
class CCodeInjectAssiantDlg : public CDialog
{
// 构造
public:
	CCodeInjectAssiantDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CCodeInjectAssiantDlg();

// 对话框数据
	enum { IDD = IDD_CODEINJECTASSIANT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	void _cdecl log_printf(char*,...);

// 实现
protected:
	HICON m_hIcon;
	int m_bHex;
	int m_bInjectDll;
	CHexEdit m_hexedit;
	CEdit m_codeedit;
	CMyPic m_wndselect;
	HMODULE m_hNtdll;
    CString m_cs_dllpath;

	LPBYTE m_pHexData;
	UINT   m_HexData_Len;
	
	HANDLE m_hProcess;	//当前被打开的进程句柄
	VOID *m_pAddrOfInject;	//
	PVOID m_pImageBaseAddress;
    UINT m_RemoteMemoryLen; //分配的远程进程的长度

	ZwQueryInformationProcess_ptr ZwQueryInformationProcess;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	void OnOK();
	void OnCancel();
	int Text2Bin(DWORD imagebaseaddress,char *outbuf,size_t len);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();


	//
	afx_msg void OnSelectProcess();	//选择要注入的进程
	afx_msg void OnOpenDllorBin();	//注入的代码或要注入的dll
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCkDll();	//选择注入Dll
	afx_msg void OnCkHex();	//使用Hex
	afx_msg void OnClick_Inject();	//注入到进程
	afx_msg void OnClick_Execute();	//执行远程线程
	afx_msg void OnClick_BlankHex();	//创建空白数据
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	//处理获取进程ID的消息
	afx_msg LRESULT OnObtainProcessID(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtInject();
};
