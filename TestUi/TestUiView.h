
// TestUiView.h : interface of the CTestUiView class
//

#pragma once
#include "OpenGl/Graphics.h"

class CTestUiView : public CView
{
protected: // create from serialization only
	CTestUiView();
	DECLARE_DYNCREATE(CTestUiView)

// Attributes
public:
	CTestUiDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTestUiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();

	CGraphics* p_graphics;

private:

	int width, height;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg LRESULT OnTxtSerChange(WPARAM, LPARAM lParam);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in TestUiView.cpp
inline CTestUiDoc* CTestUiView::GetDocument() const
   { return reinterpret_cast<CTestUiDoc*>(m_pDocument); }
#endif

