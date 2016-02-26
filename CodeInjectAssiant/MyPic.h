#ifndef _MYPIC_H_
#define _MYPIC_H_

class CMyPic : public CStatic
{
public:
	CMyPic();

public:
	void setParentWnd(HWND hWnd);

public:
	HWND m_parentwnd;
public:
	virtual ~CMyPic();

protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
private:
	CStatic m_mypic;
};

#endif //_MYPIC_H_
