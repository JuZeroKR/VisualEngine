
// VisualEngineDlg.h : header file
//

// User Add
#include "MOpenGL.h"
#include "OGV2DPoint.h"
#include "OGV2DLine.h"
#include "OGV2DBeizerCurve.h"
#include "OGVVisu.h"

#include "BagRep2D.h"
#include "OGVViewer.h"
#pragma once


// CVisualEngineDlg dialog
class CVisualEngineDlg : public CDialogEx
{
// Construction
public:
	CVisualEngineDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VISUALENGINE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_window;
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

public:
	MOpenGL* pMOpenGL;
	vector<OGV2DPoint> m_points;
	OGVVisu* pVisu;
	OGVViewer* m_pViewer;
	BagRep2D* m_pMainBagRep2D;

	// Line
	vector<OGV2DPoint> m_TempPoints;
	OGV2DPoint tempPoint;
	OGV2DPoint tempPoint2;

	int m_BezierCount;

	enum Status {
		Draw_Noting,
		Draw_Point,
		Draw_Line1,
		Draw_Line2,
		Draw_BeizerCurve,
	};

	Status m_CurStatus;

	afx_msg void OnBnClickedButtonclear();
	afx_msg void OnBnClickedButtonpoint();
	afx_msg void OnBnClickedButtonline();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonbeizercurve();
//	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};
