// cpathdia.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPATHDialog dialog

class CPATHDialog : public CDialog
{
public:
    CPATHDialog(CWnd* pParent = NULL);    // standard constructor

// Dialog Data
    //{{AFX_DATA(CPATHDialog)
	enum	{	IDD = IDD_PATH};
	CString		m_path;
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
    // Generated message map functions
    //{{AFX_MSG(CPATHDialog)
        // NOTE - the ClassExpress will add and remove member functions here.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP();

};

/////////////////////////////////////////////////////////////////////////////

