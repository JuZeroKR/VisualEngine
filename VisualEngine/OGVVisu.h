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

	

public:
	OGVVisu(CDialog* pMainWindow);
	~OGVVisu();
	void Initialize();
	void Clear();

	void ConvertCoordinate(float i_x, float i_y, float &io_x, float &io_y);

	void DrawPoint(float i_x, float i_y);
	void DrawPoint(OGV2DPoint i_point);
	void DrawLine(OGV2DPoint* i_point, OGV2DPoint* i_point2);
	void DrawLine(OGV2DLine* i_Line);

public:
	vector<OGV2DPoint*> m_points;
	vector<OGV2DLine*> m_lines;
};

