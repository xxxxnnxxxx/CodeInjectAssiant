
// CodeInjectAssianAdvDoc.h : CCodeInjectAssianAdvDoc ��Ľӿ�
//


#pragma once


class CCodeInjectAssianAdvDoc : public CDocument
{
protected: // �������л�����
	CCodeInjectAssianAdvDoc();
	DECLARE_DYNCREATE(CCodeInjectAssianAdvDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CCodeInjectAssianAdvDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


