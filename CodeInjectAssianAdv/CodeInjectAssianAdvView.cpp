
// CodeInjectAssianAdvView.cpp : CCodeInjectAssianAdvView ���ʵ��
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

// CCodeInjectAssianAdvView ����/����

CCodeInjectAssianAdvView::CCodeInjectAssianAdvView()
{
	// TODO: �ڴ˴���ӹ������

}

CCodeInjectAssianAdvView::~CCodeInjectAssianAdvView()
{
}

BOOL CCodeInjectAssianAdvView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCodeInjectAssianAdvView ����

void CCodeInjectAssianAdvView::OnDraw(CDC* /*pDC*/)
{
	CCodeInjectAssianAdvDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
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


// CCodeInjectAssianAdvView ���

#ifdef _DEBUG
void CCodeInjectAssianAdvView::AssertValid() const
{
	CView::AssertValid();
}

void CCodeInjectAssianAdvView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCodeInjectAssianAdvDoc* CCodeInjectAssianAdvView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCodeInjectAssianAdvDoc)));
	return (CCodeInjectAssianAdvDoc*)m_pDocument;
}
#endif //_DEBUG


// CCodeInjectAssianAdvView ��Ϣ�������
