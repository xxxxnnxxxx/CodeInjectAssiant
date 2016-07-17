
// CodeInjectAssianAdvView.cpp : CCodeInjectAssianAdvView 类的实现
//

#include "stdafx.h"
#include "CodeInjectAssianAdv.h"

#include "CodeInjectAssianAdvDoc.h"
#include "CodeInjectAssianAdvView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCodeInjectAssianAdvView

IMPLEMENT_DYNCREATE(CCodeInjectAssianAdvView, CView)

BEGIN_MESSAGE_MAP(CCodeInjectAssianAdvView, CView)
END_MESSAGE_MAP()

// CCodeInjectAssianAdvView 构造/析构

CCodeInjectAssianAdvView::CCodeInjectAssianAdvView()
{
	// TODO: 在此处添加构造代码

}

CCodeInjectAssianAdvView::~CCodeInjectAssianAdvView()
{
}

BOOL CCodeInjectAssianAdvView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CCodeInjectAssianAdvView 绘制

void CCodeInjectAssianAdvView::OnDraw(CDC* /*pDC*/)
{
	CCodeInjectAssianAdvDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}

void CCodeInjectAssianAdvView::OnRButtonUp(UINT nFlags, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCodeInjectAssianAdvView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
}


// CCodeInjectAssianAdvView 诊断

#ifdef _DEBUG
void CCodeInjectAssianAdvView::AssertValid() const
{
	CView::AssertValid();
}

void CCodeInjectAssianAdvView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCodeInjectAssianAdvDoc* CCodeInjectAssianAdvView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCodeInjectAssianAdvDoc)));
	return (CCodeInjectAssianAdvDoc*)m_pDocument;
}
#endif //_DEBUG


// CCodeInjectAssianAdvView 消息处理程序
