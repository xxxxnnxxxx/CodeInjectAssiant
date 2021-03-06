
// CodeInjectAssiantDlg.cpp : 实现文件
//

#include "stdafx.h"
#include <Shlwapi.h>
#include <Psapi.h>
#include "CodeInjectAssiant.h"
#include "CodeInjectAssiantDlg.h"
#include "Dlg_About.h"

#include "proc.h"


#include "DlgProcList.h"
#define _get_proc_address(x,y,z) \
	x=(z##_ptr)GetProcAddress(y,#z);\
	if(x==NULL)\
	return; 

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

CCodeInjectAssiantDlg::CCodeInjectAssiantDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCodeInjectAssiantDlg::IDD, pParent),m_bHex(0),m_bInjectDll(0),
    m_hProcess(NULL),m_pHexData(NULL),
	m_HexData_Len(0),m_RemoteMemoryLen(0),
    m_pAddrOfInject(NULL),m_ExceuteEntity(NULL),
    m_LenOfExecuteEntiry(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CCodeInjectAssiantDlg::~CCodeInjectAssiantDlg()
{
	if(m_pHexData!=NULL){
		free(m_pHexData);
		m_HexData_Len=0;
	}

    if(m_hProcess!=NULL){
        if(m_pAddrOfInject!=NULL){
            VirtualFreeEx(m_hProcess,m_pAddrOfInject,m_RemoteMemoryLen,MEM_RELEASE);
            m_pAddrOfInject=NULL;
        }

        CloseHandle(m_hProcess);
    }
}
void CCodeInjectAssiantDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Check(pDX,IDC_CK_DLL,m_bInjectDll);
	DDX_Check(pDX,IDC_CK_HEX,m_bHex);
	DDX_Control(pDX,IDC_EDITOR,m_codeedit);
	DDX_Control(pDX,IDC_ST_DRAG,m_wndselect);
	DDX_Control(pDX,IDC_EDITOR_HEX,m_hexedit);
}

BEGIN_MESSAGE_MAP(CCodeInjectAssiantDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CK_DLL,OnCkDll)
	ON_BN_CLICKED(IDC_CK_HEX,OnCkHex)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BT_SELECTFILE,OnOpenDllorBin)
	ON_BN_CLICKED(IDC_ST_PROCLIST,OnSelectProcess)
	ON_MESSAGE(WM_SENDPROCESSID,OnObtainProcessID)
	ON_BN_CLICKED(IDC_BT_ALLOCMEM,OnClick_AllocMem)
    ON_BN_CLICKED(IDC_BT_WRITEMEM,OnClick_Writemem)
	ON_BN_CLICKED(IDC_BT_EXECUTE,OnClick_Execute)
	ON_BN_CLICKED(IDC_BT_BLANKHEX,OnClick_BlankHex)
    
    ON_BN_CLICKED(ID_MENU_REMOTETHREADINJECT,OnMenu_RemoteThreadInject)
    ON_BN_CLICKED(ID_MENU_ENTRYINJECT,OnMenu_EntryInject)
    ON_BN_CLICKED(ID_MENU_About, OnAbout)
END_MESSAGE_MAP()


// CCodeInjectAssiantDlg 消息处理程序

BOOL CCodeInjectAssiantDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

    InitControl();
   

	m_wndselect.setParentWnd(m_hWnd);

	((CEdit*)((this->GetDlgItem(IDC_EDITOR))))->ShowWindow(!m_bHex);
	((CEdit*)((this->GetDlgItem(IDC_EDITOR_HEX))))->ShowWindow(m_bHex);
	this->GetDlgItem(IDC_BT_BLANKHEX)->EnableWindow(m_bHex);
	this->GetDlgItem(IDC_ET_HEXSIZE)->EnableWindow(m_bHex);
	this->GetDlgItem(IDC_CK_DLL)->EnableWindow(!m_bHex);

    this->GetDlgItem(IDC_ET_FILEPATH)->EnableWindow(m_bInjectDll&m_bHex);
    this->GetDlgItem(IDC_BT_SELECTFILE)->EnableWindow(m_bInjectDll&m_bHex);
	
	m_hexedit.SetOptions(1, 1, 1, 1);
	m_hexedit.SetBPR(16);
	m_hNtdll=::GetModuleHandle("ntdll.dll");
    InitLibFuncs();
	return TRUE;
}

void CCodeInjectAssiantDlg::InitLibFuncs()
{
    _get_proc_address(ZwQueryInformationProcess,m_hNtdll,ZwQueryInformationProcess);
}

//
struct _bt_pair_{
    UINT strid;
    UINT btid;
}g_bt_pair[]={
    {IDS_BT_ALLOCMEM,IDC_BT_ALLOCMEM},
    {IDS_BT_WRITEMEM,IDC_BT_WRITEMEM},
    {IDS_BT_EXECUTE,IDC_BT_EXECUTE},
    {IDS_BT_BLANKHEX,IDC_BT_BLANKHEX},
    {0,0}
};

void CCodeInjectAssiantDlg::InitControl()
{
    struct _bt_pair_ *ppair=g_bt_pair;
    int ret=0;
    HINSTANCE hInst=AfxGetInstanceHandle();
    for(;;)
    {
        if(ppair->btid==0 && ppair->strid==0)break;
        char strWindowText[512]={0};
        ret=::LoadStringA(hInst,ppair->strid,strWindowText,512); 
        if(ret)this->SetDlgItemText(ppair->btid,strWindowText);

        ppair++;
    }
}

void CCodeInjectAssiantDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CCodeInjectAssiantDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CCodeInjectAssiantDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
extern HWND g_hWnd;
void CCodeInjectAssiantDlg::OnTimer(UINT nIDEvent) 
{
	POINT   pnt;
	RECT    rc;
	HWND    DeskHwnd    = ::GetDesktopWindow();
	HDC     DeskDC      = ::GetWindowDC(DeskHwnd);
	int     oldRop2     =   SetROP2(DeskDC, R2_NOTXORPEN);
    RECT    currentRc; 

    this->GetWindowRect(&currentRc);
	GetCursorPos(&pnt);
	g_hWnd= ::WindowFromPoint(pnt) ;           
    
    if(::PtInRect(&currentRc,pnt))
        goto dail;

	::GetWindowRect(g_hWnd, &rc); 

	if( rc.left < 0 ) rc.left = 0;
	if (rc.top < 0 ) rc.top = 0;
	HPEN newPen = ::CreatePen(0, 3, RGB(125,0,125));
	HGDIOBJ oldPen = ::SelectObject(DeskDC, newPen);
	::Rectangle(DeskDC, rc.left, rc.top, rc.right, rc.bottom);
    ::Sleep(400);
	::Rectangle( DeskDC, rc.left, rc.top, rc.right, rc.bottom);

	::SetROP2(DeskDC, oldRop2);
	::SelectObject( DeskDC, oldPen);
	::DeleteObject(newPen);
	::ReleaseDC( DeskHwnd, DeskDC);
	DeskDC = NULL;


dail:
	CDialog::OnTimer(nIDEvent);
}

void _cdecl CCodeInjectAssiantDlg::log_printf(ULONG type,UINT strid_format,...)
{
    va_list args;
    int     len;
    char    *buffer;
    CString strLog;
    CString strTmp;
    char    szStr[512]={0};
    int     ret=0;

    ret=::LoadStringA(AfxGetInstanceHandle(),strid_format,szStr,500);
    if(ret)
    {
        switch(type)
        {
        case LOG_SUCCESS:
            strTmp=_T("[*]----");
            break;
        case LOG_ERROR:
            strTmp=_T("[!]----");
            break;
        case LOG_WARNING:
            strTmp=_T("[?]----");
            break;
        }


        va_start( args, strid_format );

        len = _vscprintf( szStr, args ); 
        buffer = (char*)malloc( (len+3) * sizeof(char));
        vsprintf_s( buffer,len+3, szStr, args ); // C4996
        strcat_s(buffer,len+3,"\r\n");
        strTmp+=CString(buffer);

        this->GetDlgItemText(IDC_ET_LOG,strLog);
        strLog+=strTmp;

        this->SetDlgItemText(IDC_ET_LOG,strLog);

        if(buffer!=NULL)
            free( buffer );

    }

}

void CCodeInjectAssiantDlg::OnOK(){}
void CCodeInjectAssiantDlg::OnCancel(){ CDialog::OnCancel();}


//
void CCodeInjectAssiantDlg::OnCkDll()
{
	UpdateData(TRUE);

	this->GetDlgItem(IDC_CK_HEX)->EnableWindow(!m_bInjectDll);
	this->GetDlgItem(IDC_EDITOR)->EnableWindow(!m_bInjectDll);

    this->GetDlgItem(IDC_ET_FILEPATH)->EnableWindow(m_bInjectDll);
    this->GetDlgItem(IDC_BT_SELECTFILE)->EnableWindow(m_bInjectDll);
}


void CCodeInjectAssiantDlg::OnCkHex()
{
	UpdateData(TRUE);

	this->GetDlgItem(IDC_CK_DLL)->EnableWindow(!m_bHex);
	this->GetDlgItem(IDC_BT_BLANKHEX)->EnableWindow(m_bHex);
	this->GetDlgItem(IDC_ET_HEXSIZE)->EnableWindow(m_bHex);
	((CEdit*)((this->GetDlgItem(IDC_EDITOR))))->ShowWindow(!m_bHex);
	((CEdit*)((this->GetDlgItem(IDC_EDITOR_HEX))))->ShowWindow(m_bHex);

    this->GetDlgItem(IDC_ET_FILEPATH)->EnableWindow(m_bHex);
    this->GetDlgItem(IDC_BT_SELECTFILE)->EnableWindow(m_bHex);
}

void CCodeInjectAssiantDlg::OnClick_BlankHex()
{
	UpdateData(TRUE);
	if(m_bHex)
    {
		if(m_pHexData!=NULL && m_HexData_Len!=0)
        {
			free(m_pHexData);
			m_pHexData=NULL;
			m_HexData_Len=0;
		}
		m_HexData_Len=this->GetDlgItemInt(IDC_ET_HEXSIZE);
		if(m_HexData_Len!=0)
        {
			m_pHexData=(LPBYTE)malloc(m_HexData_Len);
			memset(m_pHexData,0,m_HexData_Len);
			m_hexedit.Clear();
			m_hexedit.SetData(m_pHexData,m_HexData_Len);
			m_hexedit.RedrawWindow();
		}

	}
}

void CCodeInjectAssiantDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CDialog::OnHScroll(nSBCode,nPos,pScrollBar);
}

//
void CCodeInjectAssiantDlg::OnOpenDllorBin()
{
	OPENFILENAMEA ofn;
	char szFileName[1024]={0};
    char szFilter[512]={0};
    char szTitle[512]={0};
    int  ret=0;


	memset(&ofn,0,sizeof(OPENFILENAME));
	ofn.lStructSize=sizeof(OPENFILENAME);
	ofn.lpstrFile=szFileName;
	ofn.nMaxFile=sizeof(szFileName);

    ret=::LoadStringA(AfxGetInstanceHandle(),m_bInjectDll?IDS_OPFNAME_DLL:IDS_OPFNAME_BIN,szTitle,512);
    if(ret) ofn.lpstrTitle=szTitle;
    ofn.hInstance=::AfxGetApp()->m_hInstance;
	if(GetOpenFileNameA(&ofn))
	{
		this->SetDlgItemText(IDC_ET_FILEPATH,szFileName);
	}

	
	if(m_bHex)
    {
		m_hexedit.Clear();
		if(m_pHexData!=NULL && m_HexData_Len!=0)
        {
			free(m_pHexData);
			m_pHexData=NULL;
			m_HexData_Len=0;
		}

		HANDLE hFile=CreateFileA(szFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
		if(hFile!=INVALID_HANDLE_VALUE)
        {
			DWORD dwReaded=0;
			DWORD filesize=0;
			filesize=GetFileSize(hFile,NULL);

			m_pHexData=(LPBYTE)malloc(filesize);
			m_HexData_Len=filesize;

			ReadFile(hFile,m_pHexData,filesize,&dwReaded,NULL);
			CloseHandle(hFile);

			m_hexedit.SetData(m_pHexData,m_HexData_Len);
			m_hexedit.RedrawWindow();
		}
	}
    else if(m_bInjectDll)
    {
        m_cs_dllpath=CString(szFileName);
    }
}


void CCodeInjectAssiantDlg::OnSelectProcess()
{
	CDlgProcList dlg(this);
	dlg.DoModal();
}

int CCodeInjectAssiantDlg::Is_RemoteProcX64(HANDLE hProcess)
{
    DWORD dwRet=0;
    BOOL bRet=FALSE;
    char opcode[1024]={0};
    PROCESS_BASIC_INFORMATION probaseinfo;
    NTSTATUS status;
    PVOID ImageBaseAddress=0;
    int result=-1;
    
    /*
    读取64位程序，ZwQueryInformationProcess会出错，所以直接就跳过
    */
    status=ZwQueryInformationProcess(m_hProcess,ProcessBasicInformation,&probaseinfo,sizeof(PROCESS_BASIC_INFORMATION),&dwRet);
    if(status==0 && probaseinfo.PebBaseAddress!=0)
    {
        PEB peb;
        bRet=::ReadProcessMemory(m_hProcess,probaseinfo.PebBaseAddress,&peb,sizeof(PROCESS_BASIC_INFORMATION),&dwRet);
        if(bRet)
        {
            ImageBaseAddress=peb.ImageBaseAddress;

            IMAGE_DOS_HEADER dosheader;
            bRet=::ReadProcessMemory(m_hProcess,ImageBaseAddress,&dosheader,sizeof(IMAGE_DOS_HEADER),&dwRet);
            if(bRet)
            {
                IMAGE_NT_HEADERS ntheaders;
                bRet=::ReadProcessMemory(m_hProcess,(LPCVOID)((DWORD)ImageBaseAddress+dosheader.e_lfanew),&ntheaders,sizeof(IMAGE_NT_HEADERS),&dwRet);
                if(bRet)
                {
                    if(ntheaders.OptionalHeader.Magic==IMAGE_NT_OPTIONAL_HDR32_MAGIC)
                        result=0;
                    else if(ntheaders.OptionalHeader.Magic==IMAGE_NT_OPTIONAL_HDR64_MAGIC)
                        result=1;
                }
            }
        }
        
    }

    return result;

}

//
LRESULT CCodeInjectAssiantDlg::OnObtainProcessID(WPARAM wParam,LPARAM lParam)
{
	DWORD dwret=0;
	DWORD procId=(DWORD)lParam;
	char szProcessPath[1024]={0};
	int error=0;
	this->SetDlgItemInt(IDC_ET_PROCID,procId);

    this->SetDlgItemText(IDC_ET_LOG,"");

	if(m_hProcess!=NULL)
    {
        if(m_pAddrOfInject!=NULL)
        {
            VirtualFreeEx(m_hProcess,m_pAddrOfInject,m_RemoteMemoryLen,MEM_RELEASE);
            if(m_pHexData!=NULL)
            {
                free(m_pHexData);
                m_pHexData=NULL;
                m_RemoteMemoryLen=0;
                m_HexData_Len=0;
            }
        }
		CloseHandle(m_hProcess);
		m_hProcess=NULL;
	}

	m_hProcess=::OpenProcess(PROCESS_ALL_ACCESS,FALSE,procId);
	if(m_hProcess!=NULL)
    {

	    error=Is_RemoteProcX64(m_hProcess);
        if(error<0)
        {
            CloseHandle(m_hProcess);
            m_hProcess=NULL;
            log_printf(LOG_SUCCESS,IDS_TIP_READREMOTEPROC);
            return 0L;
        }
        else if(error==1)
        {
            CloseHandle(m_hProcess);
            m_hProcess=NULL;
            log_printf(LOG_SUCCESS,IDS_TIP_X64IGNORE);
            return 0L;
        }


		dwret=GetProcessImageFileNameA((HMODULE)m_hProcess,szProcessPath,1024);
		if(!dwret)
        {
            log_printf(LOG_ERROR,IDS_PROCMSG_GETPATHFAILD);
            return 0L;
		}
		
        char*processname=PathFindFileNameA(szProcessPath);
		if(processname!=NULL)
        {
			this->SetDlgItemText(IDC_ET_PROCINFO,processname);
		}
        log_printf(LOG_SUCCESS,IDS_PROCMSG_GETNAME,processname);
	}
	
	return 0L;
}

#include "disfuncs.h"

int CCodeInjectAssiantDlg::Text2Bin(DWORD imagebaseaddress,char *outbuf,size_t len)
{
	int current_size=0;
	char opcode[50]={0};
	char code[40]={0};
	int i=0;

	CString strAsm;
	this->GetDlgItemText(IDC_EDITOR,strAsm);
	strAsm.Trim();
	if(strAsm.IsEmpty())
    {
		return 0;
	}
	for(i=0;i<m_codeedit.GetLineCount();i++)
    {
		if(m_codeedit.GetLine(i,code,40))
        {
			memset(opcode,0,50);
			int opcode_size=get_opcodefromasminst(imagebaseaddress,code,opcode);
			if(opcode_size!=0)
			{
				memcpy(outbuf+current_size,opcode,opcode_size);
				current_size+=opcode_size;
			}
		}

	}
	return current_size;
}


void CCodeInjectAssiantDlg::OnClick_AllocMem()
{
	//obtain the baseaddress of process
    try{
        if(m_hProcess!=NULL)
        {
	        PROCESS_BASIC_INFORMATION probaseinfo;
	        DWORD dwRet=0;
            BOOL bRet=FALSE;
            char opcode[1024]={0};

            m_ExceuteEntity=NULL;
    		
	        NTSTATUS status=ZwQueryInformationProcess(m_hProcess,ProcessBasicInformation,&probaseinfo,sizeof(PROCESS_BASIC_INFORMATION),&dwRet);
	        if(status==0 && probaseinfo.PebBaseAddress!=0)
            {
		        PEB peb;
		        bRet=::ReadProcessMemory(m_hProcess,probaseinfo.PebBaseAddress,&peb,sizeof(PROCESS_BASIC_INFORMATION),&dwRet);
		        if(bRet)
                {
			        m_pImageBaseAddress=peb.ImageBaseAddress;
		        }
		        else
                {
			        log_printf(LOG_ERROR,IDS_PROCMSG_ALLOCMEMFAILD);
                    return;
		        }

                if(m_pAddrOfInject!=NULL && m_RemoteMemoryLen!=0)
                {
                    VirtualFreeEx(m_hProcess,m_pAddrOfInject,m_RemoteMemoryLen,MEM_RELEASE);
                    m_pAddrOfInject=NULL;
                    m_RemoteMemoryLen=0;
                }

                m_bReadytoExecute=FALSE;
                if(m_bHex)
                {   
                    if(m_HexData_Len!=0 && m_pHexData!=NULL)
                    {
                        m_RemoteMemoryLen=m_HexData_Len;
                        m_hexedit.GetData(m_pHexData,m_HexData_Len);
                        m_bReadytoExecute=TRUE;
                        m_ExceuteEntity=m_pHexData;
                    }
                }
                else if(m_bInjectDll)
                {
                    if(!m_cs_dllpath.IsEmpty())
                    {
                        char *pBuf=NULL;
                        m_RemoteMemoryLen=proc_bin_len;

                        pBuf=(char*)(proc_bin+(proc_bin_len-10*8));
                        memcpy(pBuf,m_cs_dllpath.GetBuffer(m_cs_dllpath.GetLength()),m_cs_dllpath.GetLength());
                        
                        m_bReadytoExecute=TRUE;
                        m_ExceuteEntity=proc_bin;
                    }
                    else
                    {
                        log_printf(LOG_ERROR,IDS_TIP_SELECTDLL);
                    }
                }
                else
                {
                    
                    m_RemoteMemoryLen=Text2Bin((DWORD)m_pImageBaseAddress,opcode,1024);
                    if(m_RemoteMemoryLen!=0)
                    {
                        m_bReadytoExecute=TRUE;
                        m_ExceuteEntity=(LPBYTE)opcode;
                    }
                    else
                    {
                        log_printf(LOG_WARNING,IDS_TIP_WRITEASM);
                    }
                }

                if(m_bReadytoExecute)
                {
                    
                    m_pAddrOfInject=VirtualAllocEx(m_hProcess,NULL,m_RemoteMemoryLen,MEM_COMMIT,PAGE_EXECUTE_READWRITE);
                    if(m_pAddrOfInject!=NULL)
                    {
                        char str[50]={0};
                        wsprintfA(str,"0x%08x",(DWORD)m_pAddrOfInject);
                        this->SetDlgItemText(IDC_ET_ADDRESS,str); 
                        log_printf(LOG_SUCCESS,IDS_TIP_ALLOCMEMSUCCESS);
                    }
                    else
                    {
                        log_printf(LOG_ERROR,IDS_TIP_ALLOCMEMFAILD);
                    }
           
                }
                
	        }

	    }//if(m_hProcess!=NULL)
        else
        {
            log_printf(LOG_ERROR,IDS_TIP_SELECTPROC);
        }
    }
	catch(...)
    {
        log_printf(LOG_ERROR,IDS_PROCMSG_ALLOCMEMFAILD);
        return;
    }
}


void CCodeInjectAssiantDlg::OnClick_Writemem()
{
    BOOL bRet=FALSE;
    DWORD dwSize=0;
    if(m_pAddrOfInject!=NULL && m_RemoteMemoryLen>0)
    {
        
        bRet=WriteProcessMemory(m_hProcess,m_pAddrOfInject,m_ExceuteEntity,m_RemoteMemoryLen,&dwSize);
        if(bRet)
        {
            log_printf(LOG_SUCCESS,IDS_TIP_WRITEPROCESSMEMORY,m_pAddrOfInject);
        }
        else
        {
            log_printf(LOG_ERROR,IDS_TIP_WRITEPROCESSMEMORYFAILD);
        }
    }
}


void CCodeInjectAssiantDlg::OnClick_Execute()
{
    HANDLE hRemoteThread=NULL;
    BOOL bRet=FALSE;
    DWORD dwSize=0;
    try
    {
        if(m_pAddrOfInject!=NULL && m_RemoteMemoryLen>0)
        {   
            hRemoteThread=CreateRemoteThread(m_hProcess,NULL,0,(LPTHREAD_START_ROUTINE)m_pAddrOfInject,NULL,0,NULL);
            if(hRemoteThread==NULL)
                log_printf(LOG_ERROR,IDS_TIP_CREATEREMOTETHREADFAILD);
            else
                log_printf(LOG_SUCCESS,IDS_TIP_CREATEREMOTETHREADSUCCESS,hRemoteThread);
        }
        else
        {
            log_printf(LOG_WARNING,IDS_TIP_INJECTMETHOD);
        }
    }
	catch(...)
    {
        log_printf(LOG_ERROR,IDS_TIP_RUNFAILD);
        return;
    }
}


//进程列表
void CCodeInjectAssiantDlg::OnMenu_RemoteThreadInject()
{
    OnSelectProcess();
    return;
}
//入口点注入
void CCodeInjectAssiantDlg::OnMenu_EntryInject()
{    
    return;
}
// About
void CCodeInjectAssiantDlg::OnAbout() {
    Dlg_About dlg(this);
    dlg.DoModal();
}
