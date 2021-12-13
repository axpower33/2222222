// cfrmodin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFrModInCndDlg dialog

class CFrModInCndDlg : public CDialog
{
public:
    CFrModInCndDlg(CWnd* pParent = NULL);    // standard constructor

// Dialog Data
    //{{AFX_DATA(CFrModInCndDlg)
	enum	{	IDD = IDD_FrModInCnd };
	int		    m_Npat;
	float		m_dt;
	float		m_Rmin;
	float		m_Rmax;
	float		m_Rmid;
	int		    m_Q;
    //}}AFX_DATA

// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
    DECLARE_MESSAGE_MAP();
    // Generated message map functions
    //{{AFX_MSG(CFrModInCndDlg)
    afx_msg void OnChangeEdit1();
    afx_msg void OnChangeEdit2();
    afx_msg void OnChangeEdit3();
    afx_msg void OnChangeEdit4();
    afx_msg void OnChangeEdit5();
    afx_msg void OnChangeEdit6();
    //}}AFX_MSG

};

/////////////////////////////////////////////////////////////////////////////

