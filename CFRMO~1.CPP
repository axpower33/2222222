// cfrmodin.cpp : implementation file
//

#include "stdafx.h"
#include "FRSHELL.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFrModInCndDlg

BEGIN_MESSAGE_MAP(CFrModInCndDlg, CDialog)
        //{{AFX_MSG_MAP(CFrModInCndDlg)
        ON_EN_CHANGE(IDC_EDIT1,OnChangeEdit1)
        ON_EN_CHANGE(IDC_EDIT2,OnChangeEdit2)
        ON_EN_CHANGE(IDC_EDIT3,OnChangeEdit3)
        ON_EN_CHANGE(IDC_EDIT4,OnChangeEdit4)
        ON_EN_CHANGE(IDC_EDIT5,OnChangeEdit5)
        ON_EN_CHANGE(IDC_EDIT6,OnChangeEdit6)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP();

CFrModInCndDlg::CFrModInCndDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CFrModInCndDlg::IDD, pParent)
{

}

void CFrModInCndDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);

    //{{AFX_DATA_MAP(CFrModInCndDlg)
        DDX_Text(pDX, IDC_EDIT1, m_Npat);
        DDV_MinMaxInt(pDX, m_Npat, 2, 10000);
        DDX_Text(pDX, IDC_EDIT2, m_dt);
        DDV_MinMaxFloat(pDX, m_dt, 0, 1);
        DDX_Text(pDX, IDC_EDIT6, m_Rmin);
        DDV_MinMaxFloat(pDX, m_Rmin, 0, 1);
        DDX_Text(pDX, IDC_EDIT4, m_Rmax);
        DDV_MinMaxFloat(pDX, m_Rmax, 0, 1);
        DDX_Text(pDX, IDC_EDIT5, m_Rmid);
        DDV_MinMaxFloat(pDX, m_Rmid, 0, 1);
        DDX_Text(pDX, IDC_EDIT3, m_Q);
        DDV_MinMaxInt(pDX, m_Q, 0, 500);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CFrModInCndDlg message handlers


void CFrModInCndDlg::OnChangeEdit1()
{
    // to do: Add your notification handler code here

}


void CFrModInCndDlg::OnChangeEdit2()
{
    // to do: Add your notification handler code here
}


void CFrModInCndDlg::OnChangeEdit3()
{
    // to do: Add your notification handler code here
}


void CFrModInCndDlg::OnChangeEdit4()
{
    // to do: Add your notification handler code here
}


void CFrModInCndDlg::OnChangeEdit5()
{
    // to do: Add your notification handler code here
}


void CFrModInCndDlg::OnChangeEdit6()
{
    // to do: Add your notification handler code here
}

