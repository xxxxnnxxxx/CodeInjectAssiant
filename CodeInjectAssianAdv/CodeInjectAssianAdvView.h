
// CodeInjectAssianAdvView.h : CCodeInjectAssianAdvView 类的接口
//


#pragma once


class CCodeInjectAssianAdvView : public CView
{
protected: // 仅从序列化创建
	CCodeInjectAssianAdvView();
	DECLARE_DYNCREATE(CCodeInjectAssianAdvView)

// 属性
public:
	CCodeInjectAssianAdvDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CCodeInjectAssianAdvView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // CodeInjectAssianAdvView.cpp 中的调试版本
inline CCodeInjectAssianAdvDoc* CCodeInjectAssianAdvView::GetDocument() const
   { return reinterpret_cast<CCodeInjectAssianAdvDoc*>(m_pDocument); }
#endif

