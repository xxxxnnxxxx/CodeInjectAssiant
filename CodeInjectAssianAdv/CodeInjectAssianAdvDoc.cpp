
// CodeInjectAssianAdvDoc.cpp : CCodeInjectAssianAdvDoc ���ʵ��
//

#include "stdafx.h"
#include "CodeInjectAssianAdv.h"

#include "CodeInjectAssianAdvDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCodeInjectAssianAdvDoc

IMPLEMENT_DYNCREATE(CCodeInjectAssianAdvDoc, CDocument)

BEGIN_MESSAGE_MAP(CCodeInjectAssianAdvDoc, CDocument)
END_MESSAGE_MAP()


// CCodeInjectAssianAdvDoc ����/����

CCodeInjectAssianAdvDoc::CCodeInjectAssianAdvDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CCodeInjectAssianAdvDoc::~CCodeInjectAssianAdvDoc()
{
}

BOOL CCodeInjectAssianAdvDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CCodeInjectAssianAdvDoc ���л�

void CCodeInjectAssianAdvDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CCodeInjectAssianAdvDoc ���

#ifdef _DEBUG
void CCodeInjectAssianAdvDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCodeInjectAssianAdvDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCodeInjectAssianAdvDoc ����
