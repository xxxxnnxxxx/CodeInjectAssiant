// MyPic.cpp : implementation file
//

#include "stdafx.h"
#include "MyPic.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPic
HWND g_hWnd;
CMyPic::CMyPic()
{
}

CMyPic::~CMyPic()
{
}

void CMyPic::setParentWnd(HWND hWnd){
	m_parentwnd=hWnd;
}
BEGIN_MESSAGE_MAP(CMyPic, CStatic)
	//{{AFX_MSG_MAP(CMyPic)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPic message handlers

void CMyPic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//MessageBox("aaaaaaaaaaaaaaaaaa");
	SetCapture();
	HCURSOR hc=LoadCursor(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDC_CURSOR1));
	::SetCursor(hc);
	HICON hicon2=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_DRAG2));
	this->SetIcon(hicon2);
	//GetDlgItem(IDOK)->SetWindowText("OK");
	//FromHandle(g_hMe)->OnTimer(1);
	FromHandle(m_parentwnd)->SetTimer(1,600,NULL);
	CStatic::OnLButtonDown(nFlags, point);
}

void CMyPic::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture();
	HICON hicon1=LoadIcon(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDI_DRAG1));
	this->SetIcon(hicon1);
	
	//g_hWnd=::WindowFromPoint(point);
	POINT pt;
	::GetCursorPos(&pt);
	g_hWnd=::WindowFromPoint(pt);

	//因为::WindowFromPoint(pt)对不可用的窗口无效，所以，为了能选中
	//灰色按钮等不可用的窗口(以进行激活等操作)，添加下面这段代码
	//读者也可以做一下试验，将下面*******间的代码注释掉，将不能选中不可用窗口

	//*******************
	
	HWND grayHwnd = ::GetWindow(g_hWnd, GW_CHILD);
	RECT tempRc;
	BOOL bFind=FALSE;
    while (grayHwnd)
	{
        ::GetWindowRect(grayHwnd, &tempRc);
		if(::PtInRect(&tempRc,pt))
		{
			bFind = TRUE;
			break;
		}
        else
            grayHwnd = ::GetWindow(grayHwnd, GW_HWNDNEXT);
        
	}//while
    if(bFind == TRUE)
    {
		bFind= FALSE;
        g_hWnd = grayHwnd;
    }
	else
        ;//Wnd=UnHwnd
	
	//通过窗体获取进程信息
	DWORD procID=0;
	GetWindowThreadProcessId(g_hWnd,&procID);

	::PostMessageA(m_parentwnd,WM_SENDPROCESSID,0,(LPARAM)procID);

	
	RECT rc;
	::GetWindowRect(g_hWnd, &rc);      //获得窗口矩形
	CString strRect;
	strRect.Format("(%d,%d),(%d,%d) %dx%d",rc.left,rc.top,rc.right,rc.bottom,
		rc.right-rc.left,rc.bottom-rc.top);
	FromHandle(m_parentwnd)->KillTimer(1);
	CStatic::OnLButtonUp(nFlags, point);
}
