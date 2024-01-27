#include "pch.h"
#include "OGVVisu.h"

void OGVVisu::Initialize(CDialog* pMainWindow)
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

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5f, 0.5f, 0.5f);
	::glEnable(GL_ALWAYS);

	glFlush();

	SwapBuffers(m_pDC->GetSafeHdc());
}

void OGVVisu::Clear()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void OGVVisu::DrawPoint(float i_x, float i_y)
{
	CPoint point(i_x, i_y);

	CRect rect;
	CRect visualWindowRect;
	m_pMainWindow->GetDlgItem(IDC_VisualWindow)->GetWindowRect(&rect);
	m_pMainWindow->ScreenToClient(&rect);
	m_pMainWindow->GetDlgItem(IDC_VisualWindow)->GetClientRect(&visualWindowRect);
	// Control Pos
	CPoint pt = rect.TopLeft();

	int width = visualWindowRect.Width();
	int height = visualWindowRect.Height();
	CPoint center = visualWindowRect.CenterPoint();

	if (point.x < abs(pt.x))
		return;
	if (point.y < abs(pt.y))
		return;

	CPoint mousePt = CPoint(point.x - abs(pt.x), point.y - abs(pt.y));


	float x = (mousePt.x - center.x) / ((float)width / 2);
	float y = (center.y - mousePt.y) / ((float)height / 2);

	OGV2DPoint* ogvPoint = new OGV2DPoint(x, y);
	m_points.push_back(ogvPoint);

	GLfloat vertices[] = {
		x, y, 0.f
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glPointSize(1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_POINTS, 0, 1);
	glDisableClientState(GL_VERTEX_ARRAY);

	glFlush();

	SwapBuffers(m_pDC->GetSafeHdc());


}

