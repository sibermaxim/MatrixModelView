
// TestUiView.cpp : implementation of the CTestUiView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TestUi.h"
#endif

#include "TestUiDoc.h"
#include "TestUiView.h"
#include "GlobalData/GlobalData.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestUiView

IMPLEMENT_DYNCREATE(CTestUiView, CView)

BEGIN_MESSAGE_MAP(CTestUiView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTestUiView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(TXS_CHANGE, OnTxtSerChange)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CTestUiView construction/destruction

CTestUiView::CTestUiView(): width(0), height(0), p_graphics(nullptr)
{
	// TODO: add construction code here
}

CTestUiView::~CTestUiView()
{
	delete p_graphics;
}

BOOL CTestUiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTestUiView drawing

void CTestUiView::OnDraw(CDC* /*pDC*/)
{
	CTestUiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (nullptr != p_graphics)
		p_graphics->Renderer();
}


// CTestUiView printing


void CTestUiView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTestUiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestUiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestUiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTestUiView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestUiView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTestUiView diagnostics

#ifdef _DEBUG
void CTestUiView::AssertValid() const
{
	CView::AssertValid();
}

void CTestUiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestUiDoc* CTestUiView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestUiDoc)));
	return (CTestUiDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestUiView message handlers


void CTestUiView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);


	CPoint point;
	point.x = cx;
	point.y = cy;

	ClientToScreen(&point);
	width = cx;
	height = cy;

	if (p_graphics != nullptr)
		p_graphics->OnSize(width, height);
}


void CTestUiView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

//	pHwnd = this->m_hWnd;
	
	p_graphics = new CGraphics(this, width, height);
	if(!p_graphics->InitializeGraphics())
	{
		delete p_graphics;
		return;
	}

	CMainFrame* pFrame = static_cast<CMainFrame*>(AfxGetApp()->m_pMainWnd);
	pFrame->m_wndDlgBar.InitStateControlData(0, 2, 10, 0, 0, 0);
	p_graphics->SetCameraPosition(0, 2, 10, 0, 0, 0);
}


void CTestUiView::OnMouseMove(UINT nFlags, CPoint point)
{
	if(MK_LBUTTON == nFlags)
	{
		if (nullptr != p_graphics)
			p_graphics->MouseMove(point.x, point.y);
	}

	CView::OnMouseMove(nFlags, point);
}

LRESULT CTestUiView::OnTxtSerChange(WPARAM, LPARAM lParam)
{
	return LRESULT();
}



void CTestUiView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//if (MK_LBUTTON == nFlags)
	{
		if (nullptr != p_graphics)
			p_graphics->SetMouse(point.x, point.y);
	}

	CView::OnLButtonDown(nFlags, point);
}
