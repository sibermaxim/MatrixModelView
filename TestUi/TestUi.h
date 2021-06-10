
// TestUi.h : main header file for the TestUi application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTestUiApp:
// See TestUi.cpp for the implementation of this class
//

class CTestUiApp : public CWinAppEx
{
public:
	CTestUiApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()


public:
	void TranslateViewMatrix(float x, float y, float z);
	void RotateViewMatrix(float rx, float ry, float rz);
	void TranslateWorldMatrix(float x, float y, float z);
	void RotateWorldMatrix(float rx, float ry, float rz);
};

extern CTestUiApp theApp;
