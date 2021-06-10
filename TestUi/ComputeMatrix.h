	#pragma once

#include "InitDialogBar.h"
#include "resource.h"
// CComputeMatrix dialog

#define TXS_CHANGE (WM_USER + 1)
//OnTxtSerChange(WPARAM, LPARAM lParam)
//ON_MESSAGE(TXS_CHANGE, OnTxtSerChange)
//	afx_msg LRESULT OnTxtSerChange(WPARAM, LPARAM lParam);

class CComputeMatrix : public CInitDialogBar
{
//	DECLARE_DYNAMIC(CComputeMatrix)

public:
	CComputeMatrix();   // standard constructor
	virtual ~CComputeMatrix();

// Dialog Data
//#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MATRIX_COMPUTE };
//#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	void OnUpdateBtResetModel(CCmdUI *pCmdUI);
	
	DECLARE_MESSAGE_MAP()

	afx_msg LRESULT OnUpdateViewmatrix(WPARAM, LPARAM lParam);


public:

	virtual void OnInitialUpdate();
	
	afx_msg void OnBnClickedBtResetModel();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChildActivate();

	void DisplayViewMatrix(float m[16]);
	void DisplayModelMatrix(float m[16]);
	void DisplayViewModelMatrix(float m[16]);

	void InitStateControlData(int x, int y, int z, int pitch, int heading, int roll);
	void InitStateControlDataModel(int x, int y, int z, int pitch, int heading, int roll);
	
private:

	int posX, posY, posZ;
	int pitch, heading, roll;
	
	int posXmod, posYmod, posZmod;
	int pitchMod, headingMod, rollMod;
	
	//������� ������
	CSliderCtrl mvPosX;
	CSliderCtrl mvPosY;
	CSliderCtrl mvPosZ;
	
	CStatic mDispPosXView;
	CStatic mDispPosYView;
	CStatic mDispPosZView;

	//�������� ������
	CSliderCtrl mvRotPitch;
	CSliderCtrl mvRotHeading;
	CSliderCtrl mvRotRoll;
	
	CStatic mvDispRotPitch;
	CStatic mvDispRotHeading;
	CStatic mvDispRotRoll;
	
	//������� ������
	CSliderCtrl mmPosX;
	CSliderCtrl mmPosY;
	CSliderCtrl mmPosZ;
	
	CStatic mmDispPosXView;
	CStatic mmDispPosYView;
	CStatic mmDispPosZView;

	//�������� ������
	CSliderCtrl mmRotPitch;
	CSliderCtrl mmRotHeading;
	CSliderCtrl mmRotRoll;
	
	CStatic mmDispRotPitch;
	CStatic mmDispRotHeading;
	CStatic mmDispRotRoll;

	CStatic mv[16];			//view �������
	CStatic mm[16];			//model �������
	CStatic mmv[16];		//modelview �������
	
public:
	afx_msg void OnBnClickedBtResetModel2();
	afx_msg void OnUpdateBtResetModel2(CCmdUI *pCmdUI);
};
