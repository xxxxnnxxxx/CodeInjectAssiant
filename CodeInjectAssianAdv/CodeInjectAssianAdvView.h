
// CodeInjectAssianAdvView.h : CCodeInjectAssianAdvView ��Ľӿ�
//


#pragma once


class CCodeInjectAssianAdvView : public CView
{
protected: // �������л�����
	CCodeInjectAssianAdvView();
	DECLARE_DYNCREATE(CCodeInjectAssianAdvView)

// ����
public:
	CCodeInjectAssianAdvDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CCodeInjectAssianAdvView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CodeInjectAssianAdvView.cpp �еĵ��԰汾
inline CCodeInjectAssianAdvDoc* CCodeInjectAssianAdvView::GetDocument() const
   { return reinterpret_cast<CCodeInjectAssianAdvDoc*>(m_pDocument); }
#endif

