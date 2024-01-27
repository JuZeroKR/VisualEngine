#pragma once
#include "OGV2DPoint.h"
#include "OGV2DLine.h"

#include <vector>
using namespace std;

class OGVVisu
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
	OGVVisu();
	void Initialize(CDialog* pMainWindow);
	void Start();
	void Clear();

	void DrawPoint(float i_x, float i_y);
	void DrawPoint(CPoint point);
	void DrawLine(OGV2DPoint i_point, OGV2DPoint i_point2);
	void DrawLine(OGV2DLine i_Line);

};

