#include "pch.h"
#include "OGVViewer.h"

OGVViewer::OGVViewer(CDialog* pMainWindow)
{
	m_pMainWindow = pMainWindow;
	m_pDC = new CClientDC(pMainWindow->GetDlgItem(IDC_VisualWindow));
	if (m_pDC == NULL)
	{
		AfxMessageBox(CString("Error Obtaining DC"));
		return;
	}

	hwndWindow = ::GetDlgItem(pMainWindow->m_hWnd, IDC_VisualWindow);
	::GetClientRect(hwndWindow, &rc);

	center = CPoint((rc.right - rc.left) / 2, (rc.bottom - rc.top) / 2);

	glewInit();

	pfd =
	{
	   sizeof(PIXELFORMATDESCRIPTOR),
	   1,
	   PFD_DRAW_TO_WINDOW |            // support window
	   PFD_SUPPORT_OPENGL |            // support OpenGL
	   PFD_DOUBLEBUFFER,               // double buffered
	   PFD_TYPE_RGBA,                  // RGBA type
	   32,                             // 32-bit color depth
	   0, 0, 0, 0, 0, 0,               // color bits ignored
	   0,                              // no alpha buffer
	   0,                              // shift bit ignored
	   0,                              // no accumulation buffer
	   0, 0, 0, 0,                     // accum bits ignored
	   24,                        // 24-bit z-buffer
	   0,                              // no stencil buffer
	   0,                              // no auxiliary buffer
	   PFD_MAIN_PLANE,                 // main layer
	   0,                              // reserved
	   0, 0, 0                         // layer masks ignored
	};

	m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);

	if (m_nPixelFormat == 0)
	{
		return;
	}

	if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		return;
	}

	// Rendering Context from DC
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	if (m_hRC == 0)
	{
		AfxMessageBox(CString("Error Creating RC"));
		return;
	}

	if (::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC) == FALSE)
	{
		AfxMessageBox(CString("Error making RC Current"));
		return;
	}

	glMatrixMode(GL_MODELVIEW);

	//glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f, 0.5f, 0.5f);
	::glEnable(GL_ALWAYS);

	glFlush();
	SwapBuffer();
}

void OGVViewer::Draw()
{
	DrawPoints();
	DrawLines();
	// Reframe();
	DrawBeizerCurves();
	SwapBuffer();
}

void OGVViewer::DrawPoints()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for (int j = 0; j < m_pMainBagRep2D->GetPoints().size(); j++)
	{
		OGV2DPoint* pt2D = m_pMainBagRep2D->GetPoints()[j];
		glVertex2f(pt2D->GetX(), pt2D->GetY());
	}

	for (int i = 0; i < m_pBagRep2Ds.size(); i++)
	{
		for (int j = 0; j < m_pBagRep2Ds[i]->GetPoints().size(); j++)
		{
			OGV2DPoint* pt2D = m_pBagRep2Ds[i]->GetPoints()[j];
			glVertex2f(pt2D->GetX(), pt2D->GetY());
		}
	}
	glEnd();
	glFlush();
}

void OGVViewer::DrawLines()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	for (int j = 0; j < m_pMainBagRep2D->GetLines().size(); j++)
	{
		OGV2DLine* line2D = m_pMainBagRep2D->GetLines()[j];
		glVertex2f(line2D->m_startX, line2D->m_startY);
		glVertex2f(line2D->m_endX, line2D->m_endY);
	}
	glEnd();
	glFlush();
}

void OGVViewer::DrawBeizerCurves()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINE_STRIP);
	for (int j = 0; j < m_pMainBagRep2D->GetBeizerCurves().size(); j++)
	{
		OGV2DBeizerCurve* beizerCurve2D = m_pMainBagRep2D->GetBeizerCurves()[j];
		for (int i = 0; i < beizerCurve2D->mPoints.size(); i++)
		{
			OGV2DPoint pt = beizerCurve2D->mPoints[i];
			glVertex2f(pt.x, pt.y);
		}
	}
	glEnd();
	glFlush();
	//glClear(GL_COLOR_BUFFER_BIT);


	/*glBegin(GL_POINTS);
	for (int j = 0; j < m_pMainBagRep2D->GetBeizerCurves().size(); j++)
	{
		OGV2DBeizerCurve* beizerCurve2D = m_pMainBagRep2D->GetBeizerCurves()[j];
		for (int i = 0; i < beizerCurve2D->mPoints.size(); i++)
		{
			OGV2DPoint pPt = beizerCurve2D->mPoints[i];
			glVertex2f(pPt.x, pPt.y);
		}
	}
	glEnd();
	glBegin(GL_LINES);
	for (int j = 0; j < m_pMainBagRep2D->GetBeizerCurves().size(); j++)
	{
		OGV2DBeizerCurve* beizerCurve2D = m_pMainBagRep2D->GetBeizerCurves()[j];
		for (int i = 0; i < beizerCurve2D->mLines.size(); i++)
		{
			OGV2DLine pLine = beizerCurve2D->mLines[i];
			glVertex2f(pLine.m_startX, pLine.m_startY);
			glVertex2f(pLine.m_endX, pLine.m_endY);
		}
	}
	glEnd();
	glFlush();*/
}

void OGVViewer::Clear()
{
	//glClearColor()
	glClear(GL_COLOR_BUFFER_BIT); // Delete the window and Buffer.
	for (int i = 0; i < m_pBagRep2Ds.size() ; i++)
	{
		m_pBagRep2Ds[i]->Empty();
	}
	m_pBagRep2Ds.clear();
	m_pMainBagRep2D->Empty();
	glFlush();
	SwapBuffer();
}

void OGVViewer::SwapBuffer()
{
	SwapBuffers(m_pDC->GetSafeHdc()); // Change BackBuffer to FrontBuffer
}

void OGVViewer::ClearBackGround()
{
}

void OGVViewer::Reframe()
{
	SwapBuffer();
}

void OGVViewer::AddBagRep2D(BagRep2D* iBagRep2D)
{
	m_pBagRep2Ds.push_back(iBagRep2D);
}

void OGVViewer::RemoveBagRep2D(BagRep2D* iBagRep2D)
{
	for (int i = 0; i < m_pBagRep2Ds.size(); i++)
	{
		if (iBagRep2D == m_pBagRep2Ds[i])
		{
			m_pBagRep2Ds.erase(m_pBagRep2Ds.begin() + i);
			break;
		}
	}
}
