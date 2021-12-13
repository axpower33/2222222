// cpathdia.cpp : implementation file
//

#include "stdafx.h"
#include "frshell.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPATHDialog

BEGIN_MESSAGE_MAP(CPATHDialog, CDialog)
    //{{AFX_MSG_MAP(CPATHDialog)
        // NOTE - the ClassExpress will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP();

CPATHDialog::CPATHDialog(CWnd* pParent /*=NULL*/)
    : CDialog(CPATHDialog::IDD, pParent)
{

    //{{AFX_DATA_INIT(CPATHDialog)
	m_path		 = "";
    //}}AFX_DATA_INIT
}

void CPATHDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CPATHDialog)
	DDX_Text(pDX, IDC_EDIT1, m_path);
	DDV_MaxChars(pDX, m_path, 10);
    //}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CPATHDialog message handlers

