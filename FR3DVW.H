//
// _PROJ_VW.H
//
// interface of the CFR3dView class
//
// Copyright (c) POWER Scintific, 1997. All Rights Reserved.
//

class CFR3dView : public CView
{

public:
	CFR3dDoc *GetDocument();

	virtual ~CFR3dView();
	virtual void OnDraw(CDC *pDC);


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CFR3dView();
	DECLARE_DYNCREATE(CFR3dView)
    virtual void Circle (float x,float y, float r,CDC *pDC,CFR3dDoc* pDoc);
    virtual void Line(float x1,float y1,float x2,float y2,CDC *pDC,CFR3dDoc* pDoc);
	virtual BOOL OnPreparePrinting(CPrintInfo *pInfo);
	virtual void OnBeginPrinting(CDC *pDC, CPrintInfo *pInfo);
	virtual void OnEndPrinting(CDC *pDC, CPrintInfo *pInfo);

	// Message maps
protected:
	DECLARE_MESSAGE_MAP()

	//{{AFX_MSG(CFR3dView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG


};

#ifndef _DEBUG	// debug version in fr3dvw.cpp
inline CFR3dDoc *CFR3dView::GetDocument()
	 { return (CFR3dDoc*) m_pDocument; }
#endif
