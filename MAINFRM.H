//
// MAINFRM.H
//
// Interface for the application frame window
//
// Copyright (c) POWER Scintific, 1997. All Rights Reserved.
//
//

class CMainFrame : public CMDIFrameWnd
{
        DECLARE_DYNAMIC(CMainFrame)

public:
        CMainFrame();
        virtual ~CMainFrame();
        virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

#ifdef _DEBUG
        virtual void AssertValid() const;
        virtual void Dump(CDumpContext& dc) const;
#endif

// Implementation
protected:

        // Member variables
        CStatusBar      m_StatusBar;
        CToolBar                m_ToolBar;

        // Message maps
protected:
        DECLARE_MESSAGE_MAP()

        //{{AFX_MSG(CMainFrame)
        afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
        afx_msg void OnPaint();
        //}}AFX_MSG
};
