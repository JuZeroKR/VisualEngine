#include "pch.h"
#include "MOpenGL.h"


MOpenGL::MOpenGL(CDialog* pMainWindow)
{
	CDC* m_pDC = new CClientDC(pMainWindow);
	if (m_pDC == NULL)
	{
		AfxMessageBox(CString("Error Obtaining DC"));
		return;
	}

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |                // support window
		PFD_SUPPORT_OPENGL |                   // support OpenGL
		PFD_DOUBLEBUFFER,                        // double buffered
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,                                      // color bits ignored
		0,                                                         // no alpha buffer
		0,                                                         // shift bit ignored
		0,                                                         // no accumulation buffer
		0, 0, 0, 0,                                              // accumulation bits ignored
		16,                                                       // 16-bit z-buffer
		0,                                                         // no stencil buffer
		0,                                                         // no auxiliary buffer
		PFD_MAIN_PLANE,                              // main layer
		0,                                                         // reserved
		0, 0, 0                                                  // layer masks ignored
	};

	int m_nPixelFormat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);

	if (m_nPixelFormat == 0)
	{
		return;
	}

	if (::SetPixelFormat(m_pDC->GetSafeHdc(), m_nPixelFormat, &pfd) == FALSE)
	{
		return;
	}

	// Rendering Context from DC
	HGLRC m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
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

	::glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	::glClearDepth(1.0f);
	::glEnable(GL_DEPTH_TEST);

	CWnd* pImage = GetDlgItem(IDC_VisualWindow);
	CRect rc;
	pImage->GetWindowRect(rc);
}

void MOpenGL::Initialize()
{
	




	//CWnd* pImage = GetDlgItem(IDC_VisualWindow);
	//CRect rc;
	//pImage->GetWindowRect(rc);
	//CDC*  m_pDC = pImage->GetDC();


	//if (NULL == m_pDC)
	//{
	//	AfxMessageBox(CString("Unable to get a DC"));
	//	return;
	//}


	//glewExperimental = GL_TRUE;
	//if (GLEW_OK != glewInit())
	//{
	//	AfxMessageBox(CString("GLEW could not be initialized!"));
	//	return;
	//}

	//GLint attribs[] =
	//{
	//	//OpenGL 3.3
	//	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
	//	WGL_CONTEXT_MINOR_VERSION_ARB, 3,
	//	// Uncomment this for forward compatibility mode
	//	//WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	//	// Uncomment this for Compatibility profile
	//	//WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
	//	// We are using Core profile here
	//	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	//	0
	//};


	//HGLRC CompHRC = wglCreateContextAttribsARB(m_pDC->GetSafeHdc(), 0, attribs);
	//if (CompHRC && wglMakeCurrent(m_pDC->GetSafeHdc(), CompHRC))
	//	m_hRC = CompHRC;
}

void MOpenGL::Start()
{
}

void MOpenGL::Clear()
{
}

