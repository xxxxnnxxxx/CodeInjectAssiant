
// CodeInjectAssianAdvDoc.cpp : CCodeInjectAssianAdvDoc 类的实现
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


// CCodeInjectAssianAdvDoc 构造/析构

CCodeInjectAssianAdvDoc::CCodeInjectAssianAdvDoc()
{
	// TODO: 在此添加一次性构造代码

}

CCodeInjectAssianAdvDoc::~CCodeInjectAssianAdvDoc()
{
}

BOOL CCodeInjectAssianAdvDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CCodeInjectAssianAdvDoc 序列化

void CCodeInjectAssianAdvDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CCodeInjectAssianAdvDoc 诊断

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


// CCodeInjectAssianAdvDoc 命令
