
// CodeInjectAssiantDlg.h : ͷ�ļ�
//

#pragma once

#include "hexeditctrl.h"
#include "MyPic.h"
#include "ntapi.h"


// CCodeInjectAssiantDlg �Ի���
class CCodeInjectAssiantDlg : public CDialog
{
// ����
public:
	CCodeInjectAssiantDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CCodeInjectAssiantDlg();

// �Ի�������
	enum { IDD = IDD_CODEINJECTASSIANT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	void _cdecl log_printf(char*,...);

// ʵ��
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
	
	HANDLE m_hProcess;	//��ǰ���򿪵Ľ��̾��
	VOID *m_pAddrOfInject;	//
	PVOID m_pImageBaseAddress;
    UINT m_RemoteMemoryLen; //�����Զ�̽��̵ĳ���

	ZwQueryInformationProcess_ptr ZwQueryInformationProcess;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	void OnOK();
	void OnCancel();
	int Text2Bin(DWORD imagebaseaddress,char *outbuf,size_t len);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();


	//
	afx_msg void OnSelectProcess();	//ѡ��Ҫע��Ľ���
	afx_msg void OnOpenDllorBin();	//ע��Ĵ����Ҫע���dll
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCkDll();	//ѡ��ע��Dll
	afx_msg void OnCkHex();	//ʹ��Hex
	afx_msg void OnClick_Inject();	//ע�뵽����
	afx_msg void OnClick_Execute();	//ִ��Զ���߳�
	afx_msg void OnClick_BlankHex();	//�����հ�����
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	//�����ȡ����ID����Ϣ
	afx_msg LRESULT OnObtainProcessID(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtInject();
};
