#include "pch.h"
#include "MOpenGL.h"


MOpenGL::MOpenGL(CDialog* pMainWindow)
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

void MOpenGL::Initialize()
{

}

void MOpenGL::Start()
{
}

void MOpenGL::Clear()
{
}

void MOpenGL::CreatePoint(CPoint point)
{
	glClear(GL_COLOR_BUFFER_BIT);

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

	// Cacl mousePt on the Control Picture
	CPoint mousePt = CPoint(point.x - abs(pt.x), point.y - abs(pt.y));


	float x = (mousePt.x - center.x) / ((float)width / 2);
	float y = (center.y - mousePt.y) / ((float)height / 2);

	OGV2DPoint* ogvPoint = new OGV2DPoint(x, y);
	m_points.push_back(ogvPoint);

	GLfloat vertices[] = {
		x, y, 0.f
	};
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	glPointSize(1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_POINTS, 0, 1);
	glDisableClientState(GL_VERTEX_ARRAY);

	glFlush();

	SwapBuffers(m_pDC->GetSafeHdc());
	
	
}

void MOpenGL::CreateLine(OGV2DPoint i_point, OGV2DPoint i_point2)
{
	GLfloat vertices[1000];
	glEnableClientState(GL_VERTEX_ARRAY);
	// glPointSize(1.0f);
	// glColor3f(1.0f, 0.0f, 0.0f);

	int j = 0;
	for (int i = 0; i < m_points.size(); i++)
	{
		vertices[j++] = m_points[i]->GetX();
		vertices[j++] = m_points[i]->GetY();
	}

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	{
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glDrawArrays(GL_LINES, 0, j);
	}
	glDisableClientState(GL_VERTEX_ARRAY);

	glFlush();

	SwapBuffers(m_pDC->GetSafeHdc());

	
}

void MOpenGL::CreateLine()
{
	GLfloat vertices[1000];
	// glPointSize(1.0f);
	// glColor3f(1.0f, 0.0f, 0.0f);

	int j = 0;
	for (int i = 0; i < m_points.size(); i++)
	{
		vertices[j++] = m_points[i]->GetX();
		vertices[j++] = m_points[i]->GetY();
	}

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	{
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glDrawArrays(GL_LINE_STRIP, 0, j/2);
	}
	glDisableClientState(GL_VERTEX_ARRAY);

	glFlush();

	SwapBuffers(m_pDC->GetSafeHdc());


}

void MOpenGL::CreateLine(const float x1, const float y1, const float x2, const float y2)
{
	GLfloat vertices[1000];
	int j = 0;
	vertices[j++] = x1;
	vertices[j++] = y1;
	vertices[j++] = x2;
	vertices[j++] = y2;
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	{
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glDrawArrays(GL_LINE_STRIP, 0, j / 2);
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glFlush();

	SwapBuffers(m_pDC->GetSafeHdc());
}

void MOpenGL::Draw()
{

}


