
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
	pMOpenGL = NULL;
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
	pMOpenGL = new MOpenGL((CDialog*)this);
	pVisu = new OGVVisu(this);
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

	PolynomialOperation* polynomialOperation;
	polynomialOperation = new PolynomialOperation();

	// OGV2DPoint pt = polynomialOperation->GetPointOnLine(OGV2DPoint(0,0), OGV2DPoint(10,10), 0.5);

	// Convert  

	
	float x, y;
	pVisu->ConvertCoordinate(point.x, point.y, x, y);

	pVisu->DrawPoint(x, y);
	
	if (pVisu->m_points.size() == 3)
	{
		pVisu->DrawLine(pVisu->m_points[0], pVisu->m_points[1]);
		pVisu->DrawLine(pVisu->m_points[1], pVisu->m_points[2]);
		vector<OGV2DLine*> lines;
		polynomialOperation->GetPointsBezierCurve(*pVisu->m_points[0], *pVisu->m_points[1], *pVisu->m_points[2]
			, lines);

		for (int i = 0; i < polynomialOperation->pointsPt1Pt2.size(); i++)
		{
			pVisu->DrawPoint(polynomialOperation->pointsPt1Pt2[i].GetX(), polynomialOperation->pointsPt1Pt2[i].GetY());
		}

		for (int i = 0; i < polynomialOperation->pointsPt2Pt3.size(); i++)
		{
			pVisu->DrawPoint(polynomialOperation->pointsPt2Pt3[i].GetX(), polynomialOperation->pointsPt2Pt3[i].GetY());
		}

		for (int i = 0; i < lines.size(); i++)
			pVisu->DrawLine(lines[i]);
	}
	

	

	//pMOpenGL->CreateLine(lines[0].m_startX, lines[0].m_startY, lines[0].m_endX, lines[0].m_endY);


	// OGVVisu* pVisu = new OGVVisu();
	// pVisu->Initialize(this);



	/*pMOpenGL->CreatePoint(point);
	if(pMOpenGL->SizePoints() > 1)
		pMOpenGL->CreateLine();*/

}
