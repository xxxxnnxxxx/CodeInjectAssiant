#include "stdafx.h"
#include "Resource.h"
#include "Dlg_About.h"



IMPLEMENT_DYNCREATE(Dlg_About, CDialog)

Dlg_About::Dlg_About(CWnd * pParent /* = NULL */):CDialog(Dlg_About::IDD, pParent) {

}

Dlg_About::~Dlg_About() {

}

void Dlg_About::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BOOL Dlg_About::OnInitDialog()
{
    CDialog::OnInitDialog();

    return TRUE; 
}

BEGIN_MESSAGE_MAP(Dlg_About, CDialog)

END_MESSAGE_MAP()