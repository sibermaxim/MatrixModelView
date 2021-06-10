// ComputeMatrix.cpp : implementation file
//

#include "stdafx.h"
#include "TestUi.h"
#include "ComputeMatrix.h"
#include "GlobalData/GlobalData.h"
#include "resource.h"
//#include "TestUiView.h"

// CComputeMatrix dialog

//IMPLEMENT_DYNAMIC(CComputeMatrix, CPaneDialog)

CComputeMatrix::CComputeMatrix()
{
	posX = 0;
	posY = 0;
	posZ = 0;

	posXmod = 0;
	posYmod = 0;
	posZmod = 0;

	pitchMod = 0;
	headingMod = 0;
	rollMod = 0;
}

CComputeMatrix::~CComputeMatrix()
{
}

void CComputeMatrix::DoDataExchange(CDataExchange* pDX)
{
	CPaneDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_POS_X, mvPosX);
	DDX_Control(pDX, IDC_POS_Y, mvPosY);
	DDX_Control(pDX, IDC_POS_Z, mvPosZ);
	DDX_Control(pDX, IDC_DISP_POS_X, mDispPosXView);
	DDX_Control(pDX, IDC_DISP_POS_Y, mDispPosYView);
	DDX_Control(pDX, IDC_DISP_POS_Z, mDispPosZView);
	DDX_Control(pDX, IDC_MV_PITCH, mvRotPitch);
	DDX_Control(pDX, IDC_MV_HEADING, mvRotHeading);
	DDX_Control(pDX, IDC_MV_ROLL, mvRotRoll);
	DDX_Control(pDX, IDC_MVDISPLAY_ROT_PITCH, mvDispRotPitch);
	DDX_Control(pDX, IDC_MVDISPLAY_ROT_HEADING, mvDispRotHeading);
	DDX_Control(pDX, IDC_MVDISPLAY_ROT_ROLL, mvDispRotRoll);
	
	DDX_Control(pDX, IDC_M_V_0, mv[0]);
	DDX_Control(pDX, IDC_M_V_1, mv[1]);
	DDX_Control(pDX, IDC_M_V_2, mv[2]);
	DDX_Control(pDX, IDC_M_V_3, mv[3]);
	DDX_Control(pDX, IDC_M_V_4, mv[4]);
	DDX_Control(pDX, IDC_M_V_5, mv[5]);
	DDX_Control(pDX, IDC_M_V_6, mv[6]);
	DDX_Control(pDX, IDC_M_V_7, mv[7]);
	DDX_Control(pDX, IDC_M_V_8, mv[8]);
	DDX_Control(pDX, IDC_M_V_9, mv[9]);
	DDX_Control(pDX, IDC_M_V_10, mv[10]);
	DDX_Control(pDX, IDC_M_V_11, mv[11]);
	DDX_Control(pDX, IDC_M_V_12, mv[12]);
	DDX_Control(pDX, IDC_M_V_13, mv[13]);
	DDX_Control(pDX, IDC_M_V_14, mv[14]);
	DDX_Control(pDX, IDC_M_V_15, mv[15]);
	
	DDX_Control(pDX, IDC_M_M_0, mm[0]);
	DDX_Control(pDX, IDC_M_M_1, mm[1]);
	DDX_Control(pDX, IDC_M_M_2, mm[2]);
	DDX_Control(pDX, IDC_M_M_3, mm[3]);
	DDX_Control(pDX, IDC_M_M_4, mm[4]);
	DDX_Control(pDX, IDC_M_M_5, mm[5]);
	DDX_Control(pDX, IDC_M_M_6, mm[6]);
	DDX_Control(pDX, IDC_M_M_7, mm[7]);
	DDX_Control(pDX, IDC_M_M_8, mm[8]);
	DDX_Control(pDX, IDC_M_M_9, mm[9]);
	DDX_Control(pDX, IDC_M_M_10, mm[10]);
	DDX_Control(pDX, IDC_M_M_11, mm[11]);
	DDX_Control(pDX, IDC_M_M_12, mm[12]);
	DDX_Control(pDX, IDC_M_M_13, mm[13]);
	DDX_Control(pDX, IDC_M_M_14, mm[14]);
	DDX_Control(pDX, IDC_M_M_15, mm[15]);
	
	DDX_Control(pDX, IDC_M_VM_0, mmv[0]);
	DDX_Control(pDX, IDC_M_VM_1, mmv[1]);
	DDX_Control(pDX, IDC_M_VM_2, mmv[2]);
	DDX_Control(pDX, IDC_M_VM_3, mmv[3]);
	DDX_Control(pDX, IDC_M_VM_4, mmv[4]);
	DDX_Control(pDX, IDC_M_VM_5, mmv[5]);
	DDX_Control(pDX, IDC_M_VM_6, mmv[6]);
	DDX_Control(pDX, IDC_M_VM_7, mmv[7]);
	DDX_Control(pDX, IDC_M_VM_8, mmv[8]);
	DDX_Control(pDX, IDC_M_VM_9, mmv[9]);
	DDX_Control(pDX, IDC_M_VM_10, mmv[10]);
	DDX_Control(pDX, IDC_M_VM_11, mmv[11]);
	DDX_Control(pDX, IDC_M_VM_12, mmv[12]);
	DDX_Control(pDX, IDC_M_VM_13, mmv[13]);
	DDX_Control(pDX, IDC_M_VM_14, mmv[14]);
	DDX_Control(pDX, IDC_M_VM_15, mmv[15]);
	
	DDX_Control(pDX, IDC_MPOS_X, mmPosX);
	DDX_Control(pDX, IDC_MPOS_Y, mmPosY);
	DDX_Control(pDX, IDC_MPOS_Z, mmPosZ);
	DDX_Control(pDX, IDC_MDISP_POS_X, mmDispPosXView);
	DDX_Control(pDX, IDC_MDISP_POS_Y, mmDispPosYView);
	DDX_Control(pDX, IDC_MDISP_POS_Z, mmDispPosZView);
	DDX_Control(pDX, IDC_MM_PITCH, mmRotPitch);
	DDX_Control(pDX, IDC_MM_HEADING, mmRotHeading);
	DDX_Control(pDX, IDC_MM_ROLL, mmRotRoll);
	DDX_Control(pDX, IDC_MVDISPLAY_MMROT_PITCH, mmDispRotPitch);
	DDX_Control(pDX, IDC_MVDISPLAY_MMROT_HEADING, mmDispRotHeading);
	DDX_Control(pDX, IDC_MVDISPLAY_MMROT_ROLL, mmDispRotRoll);

}

void CComputeMatrix::OnUpdateBtResetModel(CCmdUI * pCmdUI)
{
	pCmdUI->Enable(TRUE);
}

LRESULT CComputeMatrix::OnUpdateViewmatrix(WPARAM, LPARAM lParam)
{
	return LRESULT();
}


BEGIN_MESSAGE_MAP(CComputeMatrix, CPaneDialog)
	ON_BN_CLICKED(IDC_BT_RESET_MODEL, &CComputeMatrix::OnBnClickedBtResetModel)
	ON_UPDATE_COMMAND_UI(IDC_BT_RESET_MODEL, OnUpdateBtResetModel)
	ON_WM_HSCROLL()
	ON_WM_CREATE()
	ON_WM_CHILDACTIVATE()
	ON_MESSAGE(UPD_VIEW_MATRIX, OnUpdateViewmatrix)
	ON_BN_CLICKED(IDC_BT_RESET_MODEL2, &CComputeMatrix::OnBnClickedBtResetModel2)
	ON_UPDATE_COMMAND_UI(IDC_BT_RESET_MODEL2, &CComputeMatrix::OnUpdateBtResetModel2)
END_MESSAGE_MAP()


// CComputeMatrix message handlers


void CComputeMatrix::OnInitialUpdate()
{
}

void CComputeMatrix::OnBnClickedBtResetModel()
{
	
}

void CComputeMatrix::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default

	char t[1000];

	if(pScrollBar == reinterpret_cast<CScrollBar*>(&mvPosX))
	{
		posX = mvPosX.GetPos();
		theApp.TranslateViewMatrix(static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(posZ));

		sprintf_s(t, "%d", static_cast<int>(posX));
		mDispPosXView.SetWindowTextA(t);
	}	
	else if(pScrollBar == reinterpret_cast<CScrollBar*>(&mvPosY))
	{
		posY = mvPosY.GetPos();
		theApp.TranslateViewMatrix(static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(posZ));

		sprintf_s(t, "%d", static_cast<int>(posY));
		mDispPosYView.SetWindowTextA(t);
	}
	else if(pScrollBar == reinterpret_cast<CScrollBar*>(&mvPosZ))
	{
		posZ = mvPosZ.GetPos();
		theApp.TranslateViewMatrix(static_cast<float>(posX), static_cast<float>(posY), static_cast<float>(posZ));

		sprintf_s(t, "%d", static_cast<int>(posZ));
		mDispPosZView.SetWindowTextA(t);
	}
	else if(pScrollBar == reinterpret_cast<CScrollBar*>(&mvRotPitch))
	{
		pitch = mvRotPitch.GetPos();
		theApp.RotateViewMatrix(static_cast<float>(pitch), static_cast<float>(heading), static_cast<float>(roll));

		sprintf_s(t, "%d", static_cast<int>(pitch));
		mvDispRotPitch.SetWindowTextA(t);
	}
	else if(pScrollBar == reinterpret_cast<CScrollBar*>(&mvRotHeading))
	{
		heading = mvRotHeading.GetPos();
		theApp.RotateViewMatrix(static_cast<float>(pitch), static_cast<float>(heading), static_cast<float>(roll));

		sprintf_s(t, "%d", static_cast<int>(heading));
		mvDispRotHeading.SetWindowTextA(t);
	}
	else if(pScrollBar == reinterpret_cast<CScrollBar*>(&mvRotRoll))
	{
		roll = mvRotRoll.GetPos();
		theApp.RotateViewMatrix(static_cast<float>(pitch), static_cast<float>(heading), static_cast<float>(roll));

		sprintf_s(t, "%d", static_cast<int>(roll));
		mvDispRotRoll.SetWindowTextA(t);
	}
	else if (pScrollBar == reinterpret_cast<CScrollBar*>(&mmPosX))
	{
		posXmod = mmPosX.GetPos();
		theApp.TranslateWorldMatrix(static_cast<float>(posXmod), static_cast<float>(posYmod), static_cast<float>(posZmod));

		sprintf_s(t, "%d", static_cast<int>(posXmod));
		mmDispPosXView.SetWindowTextA(t);
	}
	else if (pScrollBar == reinterpret_cast<CScrollBar*>(&mmPosY))
	{
		posYmod = mmPosY.GetPos();
		theApp.TranslateWorldMatrix(static_cast<float>(posXmod), static_cast<float>(posYmod), static_cast<float>(posZmod));

		sprintf_s(t, "%d", static_cast<int>(posYmod));
		mmDispPosYView.SetWindowTextA(t);
	}
	else if (pScrollBar == reinterpret_cast<CScrollBar*>(&mmPosZ))
	{
		posZmod = mmPosZ.GetPos();
		theApp.TranslateWorldMatrix(static_cast<float>(posXmod), static_cast<float>(posYmod), static_cast<float>(posZmod));

		sprintf_s(t, "%d", static_cast<int>(posZmod));
		mmDispPosZView.SetWindowTextA(t);
	}
	else if (pScrollBar == reinterpret_cast<CScrollBar*>(&mmRotPitch))
	{
		pitchMod = mmRotPitch.GetPos();
		theApp.RotateWorldMatrix(static_cast<float>(pitchMod), static_cast<float>(headingMod), static_cast<float>(rollMod));

		sprintf_s(t, "%d", static_cast<int>(pitchMod));
		mmDispRotPitch.SetWindowTextA(t);
	}
	else if (pScrollBar == reinterpret_cast<CScrollBar*>(&mmRotHeading))
	{
		headingMod = mmRotHeading.GetPos();
		theApp.RotateWorldMatrix(static_cast<float>(pitchMod), static_cast<float>(headingMod), static_cast<float>(rollMod));

		sprintf_s(t, "%d", static_cast<int>(headingMod));
		mmDispRotHeading.SetWindowTextA(t);
	}
	else if (pScrollBar == reinterpret_cast<CScrollBar*>(&mmRotRoll))
	{
		rollMod = mmRotRoll.GetPos();
		theApp.RotateWorldMatrix(static_cast<float>(pitchMod), static_cast<float>(headingMod), static_cast<float>(rollMod));

		sprintf_s(t, "%d", static_cast<int>(rollMod));
		mmDispRotRoll.SetWindowTextA(t);
	}

	else
		CInitDialogBar::OnHScroll(nSBCode, nPos, pScrollBar);
}


int CComputeMatrix::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CInitDialogBar::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}


void CComputeMatrix::OnChildActivate()
{
	CInitDialogBar::OnChildActivate();
	//CMainFrame* pFrame = static_cast<CMainFrame*>(AfxGetApp()->m_pMainWnd);
	pHwndPane = this->m_hWnd;

	mvPosX.SetRange(-10, 10, TRUE);
	mvPosY.SetRange(-10, 10, TRUE);
	mvPosZ.SetRange(-20, 20, TRUE);
	
	mmPosX.SetRange(-10, 10, TRUE);
	mmPosY.SetRange(-10, 10, TRUE);
	mmPosZ.SetRange(-10, 10, TRUE);

	mvRotPitch.SetRange(-180, 180, TRUE);
	mvRotHeading.SetRange(-180, 180, TRUE);
	mvRotRoll.SetRange(-180, 180, TRUE);
	
	mmRotPitch.SetRange(-180, 180, TRUE);
	mmRotHeading.SetRange(-180, 180, TRUE);
	mmRotRoll.SetRange(-180, 180, TRUE);
}

/***********************************************************************
	функция:			DisplayViewMatrix()
	назначение:			Отображение матрицы вида
	входные данные:		m[16] - матрица вида
	выходные данные:	нет
**********************************************************************/
void CComputeMatrix::DisplayViewMatrix(float m[16])
{
	char t[1000];
	
	for(int i=0; i<16; i++)
	{
		sprintf_s(t, "%.2f", static_cast<double>(m[i]));
		mv[i].SetWindowTextA(t);
	}
}

/***********************************************************************
	функция:			DisplayModelMatrix()
	назначение:			Отображение матрицы модели
	входные данные:		m[16] - матрица модели
	выходные данные:	нет
**********************************************************************/
void CComputeMatrix::DisplayModelMatrix(float m[16])
{
	char t[1000];

	for (int i = 0; i < 16; i++)
	{
		sprintf_s(t, "%.2f", static_cast<double>(m[i]));
		mm[i].SetWindowTextA(t);
	}
}

/***********************************************************************
	функция:			DisplayModelMatrix()
	назначение:			Отображение матрицы модели вида
	входные данные:		m[16] - матрица модели вида
	выходные данные:	нет
**********************************************************************/
void CComputeMatrix::DisplayViewModelMatrix(float m[16])
{
	char t[1000];

	for (int i = 0; i < 16; i++)
	{
		sprintf_s(t, "%.2f", static_cast<double>(m[i]));
		mmv[i].SetWindowTextA(t);
	}
}

/***********************************************************************
	функция:			InitStateControlData()
	назначение:			Инициализация элементов управления начальными значениями
	входные данные:		x, y, z, rx, ry, rz - начальные значения
	выходные данные:	нет
**********************************************************************/
void CComputeMatrix::InitStateControlData(int x, int y, int z, int pitch, int heading, int roll)
{
	char t[1000];
	
	mvPosX.SetPos(x);
	sprintf_s(t, "%d", static_cast<int>(x));
	mDispPosXView.SetWindowTextA(t);

	mvPosY.SetPos(y);
	sprintf_s(t, "%d", static_cast<int>(y));
	mDispPosYView.SetWindowTextA(t);
	
	mvPosZ.SetPos(z);
	sprintf_s(t, "%d", static_cast<int>(z));
	mDispPosZView.SetWindowTextA(t);
	
	posX = x;
	posY = y;
	posZ = z;

	mvRotPitch.SetPos(x);
	sprintf_s(t, "%d", static_cast<int>(pitch));
	mvDispRotPitch.SetWindowTextA(t);

	mvRotHeading.SetPos(y);
	sprintf_s(t, "%d", static_cast<int>(heading));
	mvDispRotHeading.SetWindowTextA(t);
	
	mvRotRoll.SetPos(z);
	sprintf_s(t, "%d", static_cast<int>(roll));
	mvDispRotRoll.SetWindowTextA(t);

	this->pitch = pitch;
	this->heading = heading;
	this->roll = roll;
}

void CComputeMatrix::InitStateControlDataModel(int x, int y, int z, int pitch, int heading, int roll)
{
	char t[1000];
	
	mmPosX.SetPos(x);
	sprintf_s(t, "%d", static_cast<int>(x));
	mmDispPosXView.SetWindowTextA(t);
}


void CComputeMatrix::OnBnClickedBtResetModel2()
{
	// TODO: Add your control notification handler code here
}


void CComputeMatrix::OnUpdateBtResetModel2(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(TRUE);
}
