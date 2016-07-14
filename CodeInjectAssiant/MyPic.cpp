#include "stdafx.h"
#include "MyPic.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


HWND g_hWnd;
CMyPic::CMyPic(){}

CMyPic::~CMyPic(){}

void CMyPic::setParentWnd(HWND hWnd){
	m_parentwnd=hWnd;
}


BEGIN_MESSAGE_MAP(CMyPic, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


void CMyPic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();
	HCURSOR hc=LoadCursor(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDC_CURSOR1));
	::SetCursor(hc);
	HICON hicon2=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_DRAG2));
	this->SetIcon(hicon2);
	FromHandle(m_parentwnd)->SetTimer(1,600,NULL);
	CStatic::OnLButtonDown(nFlags, point);
}

void CMyPic::OnLButtonUp(UINT nFlags, CPoint point) 
{
	
    POINT pt;
    DWORD procID=0;     //窗口所在进程
    DWORD curprocID=0;  //获取当前进程ID
    BOOL bFind=FALSE;
    HICON hDrg;

    GetCursorPos(&pt);
    g_hWnd=::WindowFromPoint(pt);

	ReleaseCapture();
	hDrg=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_DRAG1));
	this->SetIcon(hDrg);
	


	
    //判断不是当前进程
	GetWindowThreadProcessId(g_hWnd,&procID);
    curprocID=GetCurrentProcessId();
    if(procID==curprocID)
        goto dail;

	::PostMessageA(m_parentwnd,WM_SENDPROCESSID,0,(LPARAM)procID);
dail:
    FromHandle(m_parentwnd)->KillTimer(1);
	CStatic::OnLButtonUp(nFlags, point);
}
