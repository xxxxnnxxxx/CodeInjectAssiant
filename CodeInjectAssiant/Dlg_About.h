#ifndef __DLG_ABOUT_H__
#define __DLG_ABOUT_H__

#include <Windows.h>


class Dlg_About: public CDialog
{
    DECLARE_DYNCREATE(Dlg_About)

public:
    Dlg_About(CWnd * pParent = NULL);
    ~Dlg_About();

    enum { IDD = IDD_ABOUTBOX };
protected:
    virtual void            DoDataExchange(CDataExchange* pDX);
    virtual BOOL            OnInitDialog();
private:
    DECLARE_MESSAGE_MAP()
};



#endif