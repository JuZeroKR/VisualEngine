
// VisualEngineDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "VisualEngine.h"
#include "VisualEngineDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVisualEngineDlg dialog



CVisualEngineDlg::CVisualEngineDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VISUALENGINE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVisualEngineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VisualWindow, m_window);
}

BEGIN_MESSAGE_MAP(CVisualEngineDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTONClear, &CVisualEngineDlg::OnBnClickedButtonclear)
	ON_BN_CLICKED(IDC_BUTTONPoint, &CVisualEngineDlg::OnBnClickedButtonpoint)
	ON_BN_CLICKED(IDC_BUTTONLine, &CVisualEngineDlg::OnBnClickedButtonline)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTONBeizerCurve, &CVisualEngineDlg::OnBnClickedButtonbeizercurve)
END_MESSAGE_MAP()


// CVisualEngineDlg message handlers

BOOL CVisualEngineDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//MOpenGL* pMOpenGL = new MOpenGL((CDialog*)this);
	// pMOpenGL = new MOpenGL((CDialog*)this);
	m_BezierCount = 3;

	CString beizerCount;
	beizerCount.Format(_T("%d"), m_BezierCount);
	GetDlgItem(IDC_EDITBeizerCount)->SetWindowTextW(beizerCount);

	m_pViewer = new OGVViewer(this);
	m_pMainBagRep2D = new BagRep2D();
	m_pViewer->SetMainBagRep2D(m_pMainBagRep2D);
	pVisu = new OGVVisu(this);
	cout << "CVisualEngineDlg::OnInitDialog() " << endl;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVisualEngineDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVisualEngineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVisualEngineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVisualEngineDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: Add your message handler code here
}


void CVisualEngineDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	// MOpenGL* pMOpenGL = new MOpenGL((CDialog*)this);
	CDialogEx::OnTimer(nIDEvent);
}

#include <iostream>
#include "PolynomialOperation.h"
#include "OGVVisu.h"

void CVisualEngineDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	CDialogEx::OnLButtonDown(nFlags, point);
	CRect rt1;
	((CStatic*)GetDlgItem(IDC_VisualWindow))->GetWindowRect(&rt1);
	ScreenToClient(&rt1);

	// OGV2DPoint pt = polynomialOperation->GetPointOnLine(OGV2DPoint(0,0), OGV2DPoint(10,10), 0.5);

	// Convert  
	float x, y;
	pVisu->ConvertCoordinate(point.x, point.y, x, y);

	if (m_CurStatus == Status::Draw_Point)
	{
		OGV2DPoint* pOGV2Dpoint = new OGV2DPoint(x, y);
		m_pMainBagRep2D->AddPoint(pOGV2Dpoint);
		m_pViewer->Draw();
	}
	else if (m_CurStatus == Status::Draw_Line1)
	{
		tempPoint = OGV2DPoint(x, y);
		//m_pMainBagRep2D->AddPoint(pOGV2Dpoint);
		//m_pViewer->Draw();

		m_CurStatus = Status::Draw_Line2;
	}
	else if (m_CurStatus == Status::Draw_Line2)
	{
		OGV2DPoint* pOGV2Dpoint1 = new OGV2DPoint(x, y);
		OGV2DPoint* pOGV2Dpoint2 = new OGV2DPoint(tempPoint.x, tempPoint.y);
		m_pMainBagRep2D->AddPoint(pOGV2Dpoint1);
		m_pMainBagRep2D->AddPoint(pOGV2Dpoint2);
		OGV2DLine* pOGV2DLine = new OGV2DLine(pOGV2Dpoint1->GetX(), pOGV2Dpoint1->GetY(),
			pOGV2Dpoint2->GetX(), pOGV2Dpoint2->GetY());
		m_pMainBagRep2D->AddLine(pOGV2DLine);
		m_pViewer->Draw();
		m_CurStatus = Status::Draw_Noting;
	}
	else if (m_CurStatus == Status::Draw_BeizerCurve)
	{
		tempPoint = OGV2DPoint(x, y);
		m_TempPoints.push_back(tempPoint);
		if (m_TempPoints.size() == m_BezierCount)
		{


			m_CurStatus = Status::Draw_Noting;
		}
		else
		{
			
		}
	}
	/*else if (m_CurStatus == Status::Draw_BeizerCurve3)
	{
		OGV2DBeizerCurve* pBeizerCurve = new OGV2DBeizerCurve(tempPoint.x, tempPoint.y, tempPoint2.x, tempPoint2.y, x, y);
		m_pMainBagRep2D->AddBeizerCurve(pBeizerCurve);
		m_pViewer->Draw();
		m_CurStatus = Status::Draw_Noting;
	}*/

	return;
}


void CVisualEngineDlg::OnBnClickedButtonclear()
{
	// TODO: Add your control notification handler code here
	m_pViewer->Clear();
	m_CurStatus = Status::Draw_Noting;
	return;
}


void CVisualEngineDlg::OnBnClickedButtonpoint()
{
	// TODO: Add your control notification handler code here
	m_CurStatus = Status::Draw_Point;

}


void CVisualEngineDlg::OnBnClickedButtonline()
{
	// TODO: Add your control notification handler code here
	m_CurStatus = Status::Draw_Line1;
}


void CVisualEngineDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialogEx::OnMouseMove(nFlags, point);
	CRect rt1;
	((CStatic*)GetDlgItem(IDC_VisualWindow))->GetWindowRect(&rt1);
	ScreenToClient(&rt1);

	cout << "X : " << point.x << " / Y : " << point.y << endl;

}


void CVisualEngineDlg::OnBnClickedButtonbeizercurve()
{
	// TODO: Add your control notification handler code here

	m_CurStatus = Status::Draw_BeizerCurve;
	CString beizerCount;
	GetDlgItem(IDC_EDITBeizerCount)->GetWindowTextW(beizerCount);
	m_BezierCount = _tstoi(beizerCount);

}
