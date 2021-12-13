//
// FRSHELL.h
//
// main header file for the application
//
// Copyright (c) POWER Scintific, 1997. All Rights Reserved.


#include "resource.h"           // main symbols
#include "cfrmodin.h"
#include "cpathdia.h"
//
// CFRSHELLApp
//

class CFRSHELLApp : public CWinApp
{
public:
   CFRSHELLApp();

    virtual BOOL InitInstance();
    BOOL OnIdle( LONG lCount );
    DECLARE_MESSAGE_MAP()

    afx_msg void OnPathDlg();
    afx_msg void OnAbout();
    afx_msg void OnFrMod_InCnd();

};

extern CFrModInCndDlg* FrMInCnd;
extern CPATHDialog* CPathDlg;


