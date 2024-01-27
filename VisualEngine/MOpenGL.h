#pragma once
//#include "VisualEngineDlg.h"
// #include "CDialogEx.h"

#include "OGV2DPoint.h"
#include <vector>
using namespace std;


class MOpenGL
{
private:
	HWND hwndWindow;
	CDC* m_pDC;
	PIXELFORMATDESCRIPTOR pfd;

	int m_nPixelFormat;

	HGLRC m_hRC;
	RECT rc;

	CPoint center;

	CDialog* m_pMainWindow;

	vector<OGV2DPoint*> m_points;

public:
	MOpenGL(CDialog* pMainWindow);

public:
	// Methods
	void Initialize();
	void Start();
	void Clear();

	void CreatePoint(CPoint point);
	void CreateLine(OGV2DPoint i_point, OGV2DPoint i_point2);
	void CreateLine();
	void CreateLine(const float x1, const float y1, const float x2, const float y2);

public:
	void Draw();

};