//
// FRSHELL.cpp
//
// Defines the class behaviors for the application.
//
// Copyright (c) POWER Scintific, 1997. All Rights Reserved.
//

#include "stdafx.h"
#include "FRSHELL.h"
#include "mainfrm.h"
#include "fr3ddoc.h"
#include "fr3dvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//
// CFRSHELLApp
//
BEGIN_MESSAGE_MAP(CFRSHELLApp, CWinApp)
        //{{AFX_MSG_MAP(CFRSHELLApp)
        ON_COMMAND(ID_APP_ABOUT, OnAbout)
        // Handlers within the section marked by {{AFX_MSG_MAP
        // and }}AFX_MSG_MAP are maintained by ClassExpress.
        //}}AFX_MSG_MAP
        ON_COMMAND(ID_FrMod_InCnd, OnFrMod_InCnd)
        ON_COMMAND(ID_PathDlg, OnPathDlg)
        // Use inherited for File/New and File/Open
        ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
        ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)

        // Use inherited for File/Print Setup
        ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)

        // Use inherited for help
        ON_COMMAND(ID_HELP_INDEX, CWinApp::OnHelpIndex)
        ON_COMMAND(ID_HELP_USING, CWinApp::OnHelpUsing)
        ON_COMMAND(ID_HELP, CWinApp::OnHelp)
        ON_COMMAND(ID_CONTEXT_HELP, CWinApp::OnContextHelp)
        ON_COMMAND(ID_DEFAULT_HELP, CWinApp::OnHelpIndex)
END_MESSAGE_MAP()

//
// CFRSHELLApp construction
//

CFrModInCndDlg* FrMInCnd;
CPATHDialog* CPathDlg;

CFRSHELLApp::CFRSHELLApp()
{
        // You can initialize member variables here.
        // Most of the initialization code, however,
        // should go into CFRSHELLApp::InitInstance().
   FrMInCnd=new CFrModInCndDlg;
   FrMInCnd->m_Npat=50;
   FrMInCnd->m_dt=2e-5;
   FrMInCnd->m_Rmin=10e-7;
   FrMInCnd->m_Rmax=30e-7;
   FrMInCnd->m_Rmid=100e-7;
   FrMInCnd->m_Q=30;

   CPathDlg=new CPATHDialog;
   CPathDlg->m_path="DAT";
}


// There is only one instance of the CFRSHELLApp object
CFRSHELLApp NEAR theApp;

//
// CFRSHELLApp initialization
//

BOOL CFRSHELLApp::InitInstance()
{
#if (_MFC_VER >= 0x0300)
        Enable3dControls();
#else
        EnableVBX();                    // Initialize VBX support
        SetDialogBkColor();             // Set dialog background color to gray
#endif

        LoadStdProfileSettings();       // Load information from the .INI

        // Register our document templates
        CMultiDocTemplate *pDocTemplate;
        pDocTemplate = new CMultiDocTemplate(IDR_MDIDOCTYPE,
                        RUNTIME_CLASS(CFR3dDoc),
                        RUNTIME_CLASS(CMDIChildWnd),
                        RUNTIME_CLASS(CFR3dView));
        AddDocTemplate(pDocTemplate);

        // Create an MDI frame window
        CMainFrame *pMainFrame = new CMainFrame;
        if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
                return FALSE;
        m_pMainWnd = pMainFrame;

        pMainFrame->ShowWindow(m_nCmdShow);
        pMainFrame->UpdateWindow();

        // simple command-line handling
        if (! m_lpCmdLine[0]) {
                OnFileNew();
        } else {
                OpenDocumentFile(m_lpCmdLine);
        }

        return TRUE;
}

//
// CAboutDlg dialog used for App About
//

class CAboutDlg : public CDialog
{
public:
        CAboutDlg();

        // Dialog Data
        //{{AFX_DATA(CAboutDlg)
        enum { IDD = IDD_ABOUTBOX };
        //}}AFX_DATA

        // Implementation
protected:
        DECLARE_MESSAGE_MAP()

        virtual void DoDataExchange(CDataExchange *pDX);
        //{{AFX_MSG(CAboutDlg)
        //}}AFX_MSG
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
        //{{AFX_DATA_INIT(CAboutDlg)
        //}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange *pDX)
{
        CDialog::DoDataExchange(pDX);
        //{{AFX_DATA_MAP(CAboutDlg)
        //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
        //{{AFX_MSG_MAP(CAboutDlg)
        // Handlers within the section marked by {{AFX_MSG_MAP and }}AFX_MSG_MAP
        // are maintained by ClassExpress.
        //}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CFRSHELLApp::OnAbout()
{
   CAboutDlg aboutDlg;
   aboutDlg.DoModal();
}

void CFRSHELLApp::OnPathDlg()
{ CPathDlg->DoModal();
}

void CFRSHELLApp::OnFrMod_InCnd()
{
   FrMInCnd->DoModal();
}

// VBX handling
//{{AFX_VBX_REGISTER_MAP()
//}}AFX_VBX_REGISTER_MAP

BOOL CFRSHELLApp::OnIdle( LONG lCount )
{
    CWinApp::OnIdle( lCount );

    int i = 5;

    while( i-- )
    {
       POSITION pos = m_templateList.GetHeadPosition();
       while (pos != NULL)
       {
          CMultiDocTemplate* pTemplate = (CMultiDocTemplate*)m_templateList.GetNext(pos);

          POSITION dPos = pTemplate->GetFirstDocPosition();
          while( dPos != NULL )
          {
             CDocument* doc = (CDocument*)pTemplate->GetNextDoc(dPos);
             doc->OnIdle();

             //if( i ) continue;

             POSITION vPos = doc->GetFirstViewPosition();
             while( vPos != NULL )
             {
                CView* view = (CView*)doc->GetNextView( vPos );
                view->Invalidate( FALSE );
                view->UpdateWindow();
             }
          }
       }
    }

    return TRUE;
}

//
// CFRSHELLApp commands
//
