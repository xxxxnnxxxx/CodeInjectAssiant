#ifndef _CODEINJECTASSIANTDLG_H_
#define _CODEINJECTASSIANTDLG_H_

#include "hexeditctrl.h"
#include "MyPic.h"
#include "ntapi.h"

class CCodeInjectAssiantDlg : public CDialog
{

public:
	CCodeInjectAssiantDlg(CWnd* pParent = NULL);
	~CCodeInjectAssiantDlg();

	enum { IDD = IDD_CODEINJECTASSIANT_DIALOG };

    enum{
        LOG_SUCCESS,
        LOG_WARNING,
        LOG_ERROR,
    };


//method
private:
    void        InitLibFuncs();
    void _cdecl log_printf(ULONG type,UINT strid_format,...);
    int         Is_RemoteProcX64(HANDLE hProcess);
    

// 实现
protected:
	HICON       m_hIcon;
	int         m_bHex;
	int         m_bInjectDll;
	CHexEdit    m_hexedit;
	CEdit       m_codeedit;
	CMyPic      m_wndselect;
	HMODULE     m_hNtdll;
    CString     m_cs_dllpath;

	LPBYTE      m_pHexData;
	UINT        m_HexData_Len;
	
	HANDLE      m_hProcess;
	VOID *      m_pAddrOfInject;
	PVOID       m_pImageBaseAddress;
    UINT        m_RemoteMemoryLen;
    BOOL        m_bReadytoExecute;
    LPBYTE      m_ExceuteEntity;
    size_t      m_LenOfExecuteEntiry;

	ZwQueryInformationProcess_ptr ZwQueryInformationProcess;

	virtual BOOL    OnInitDialog();
            void    InitControl();  //初始化控件
    virtual void    DoDataExchange(CDataExchange* pDX);
	        void    OnOK();
	        void    OnCancel();
	        int     Text2Bin(DWORD imagebaseaddress,char *outbuf,size_t len);
	afx_msg void    OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void    OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();


	//
	afx_msg void    OnSelectProcess();	    //选择要注入的进程
	afx_msg void    OnOpenDllorBin();	    //注入的代码或要注入的dll
	afx_msg void    OnTimer(UINT nIDEvent);
	afx_msg void    OnCkDll();	            //选择注入Dll
	afx_msg void    OnCkHex();	            //使用Hex
	afx_msg void    OnClick_AllocMem();	    //注入到进程
    afx_msg void    OnClick_Writemem();     //写入内存
	afx_msg void    OnClick_Execute();	    //执行远程线程
	afx_msg void    OnClick_BlankHex(); 	//创建空白数据
	afx_msg void    OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg LRESULT OnObtainProcessID(WPARAM wParam,LPARAM lParam);//处理获取进程ID的消息
    afx_msg void    OnBnClickedBtInject();

    afx_msg void    OnMenu_RemoteThreadInject();      //进程列表
    afx_msg void    OnMenu_EntryInject();   //入口注入方式
	DECLARE_MESSAGE_MAP()
};


#endif