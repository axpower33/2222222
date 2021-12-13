#include "stdafx.h"
#include "FRSHELL.h"
#include <math.h>
#include "fr3ddoc.h"
#include "fr3dvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//
// CFR3dView
//
CPen bluePen=CPen(PS_SOLID, 1, RGB(0,0,255)),
     redPen =CPen(PS_SOLID, 1, RGB(255,0,0)),
     magPen =CPen(PS_SOLID, 1, RGB(255,0,255));

CBrush redBrush=CBrush( RGB(255,0,0) ),
       blackBrush = CBrush( RGB(0,0,0) ),
       blueBrush = CBrush( RGB(0,0,255) ),
       magBrush = CBrush( RGB(255,0,255) );

IMPLEMENT_DYNCREATE(CFR3dView, CView)

BEGIN_MESSAGE_MAP(CFR3dView, CView)
	//{{AFX_MSG_MAP(CFR3dView)
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
        //}}AFX_MSG_MAP

        // Use superclass for File/Print and File/Print Preview
    ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
    ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

//
// CFR3dView constructor
//

CFR3dView::CFR3dView()
{
        // to do: add construction code here
}

//
// CFR3dView destructor
//

CFR3dView::~CFR3dView()
{
}

int round(float v)
{
 return(v+0.5);
}

void CFR3dView::Circle (float x,float y, float r,CDC *pDC,CFR3dDoc* pDoc)
{
 pDC->Ellipse(round((x-r-pDoc->GetminX)*pDoc->rangeX),
              round((pDoc->GetScY-(y-r)+pDoc->GetminY)*pDoc->rangeY),
              round((x+r-pDoc->GetminX)*pDoc->rangeX),
              round((pDoc->GetScY-(y+r)+pDoc->GetminY)*pDoc->rangeY));
}

void CFR3dView::Line(float x1,float y1,float x2,float y2,CDC *pDC,CFR3dDoc* pDoc)
{
  pDC->MoveTo(round((x1-pDoc->GetminX)*pDoc->rangeX),round((pDoc->GetScY-y1+pDoc->GetminY)*pDoc->rangeY));
  pDC->LineTo(round((x2-pDoc->GetminX)*pDoc->rangeX),round((pDoc->GetScY-y2+pDoc->GetminY)*pDoc->rangeY));
}


void CFR3dView::OnDraw(CDC *pDC)
{
    CRect r;
    GetClientRect( &r );

    CFR3dDoc *pDoc = GetDocument();
    pDoc->rangeX=r.right/pDoc->GetScX;
    pDoc->rangeY=r.bottom/pDoc->GetScY;
    pDoc->rangeR=sqrt(pow(pDoc->rangeX,2)+pow(pDoc->rangeY,2));

    pDC->FillRect( r, &blackBrush );
    pDC->SelectStockObject( BLACK_BRUSH );
    for(pDoc->Pi=pDoc->FirstPat;pDoc->Pi!=NULL;pDoc->Pi=pDoc->Pi->next)
    {
      if (pDoc->Pi->q!=0) pDC->SelectObject( pDoc->Pi->q>0 ? &redPen : &bluePen );
      else pDC->SelectObject( &magPen );
      Circle(pDoc->Pi->X, pDoc->Pi->Y, pDoc->Pi->R, pDC, pDoc);
    }

 //   Line(pDoc->GetminX,pDoc->GetminY,pDoc->GetmaxX,pDoc->GetmaxY,pDC,pDoc);
}

BOOL CFR3dView::OnPreparePrinting(CPrintInfo *pInfo)
{
   return DoPreparePrinting(pInfo);
}

void CFR3dView::OnBeginPrinting(CDC */*pDC*/, CPrintInfo */*pInfo*/)
{
}

void CFR3dView::OnEndPrinting(CDC */*pDC*/, CPrintInfo */*pInfo*/)
{
}

//
// CFR3dView debug diagnostics
//

#ifdef _DEBUG
void CFR3dView::AssertValid() const
{
        CView::AssertValid();
}

void CFR3dView::Dump(CDumpContext& dc) const
{
        CView::Dump(dc);
}

CFR3dDoc *CFR3dView::GetDocument()
{
        ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFR3dDoc)));
        return (CFR3dDoc *) m_pDocument;
}

#endif

//
// CFR3dView message handlers
//

BOOL CFR3dView::OnEraseBkgnd(CDC* pDC)
{
    // to do: Add your message handler code here and/or call default

    return CView::OnEraseBkgnd(pDC);
}


int CFR3dView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // to do: Add your specialized creation code here

    return 0;
}

