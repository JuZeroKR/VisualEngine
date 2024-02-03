#pragma once
/*
Visualization Main Frame



*/

#include "BagRep2D.h"

class OGVViewer
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
	OGVViewer(CDialog* pMainWindow);
	void Draw();
	void DrawPoints();
	void DrawLines();
	void DrawBeizerCurves();

	void Clear();
	void SwapBuffer();
	void ClearBackGround();
	void Reframe();
	
	void SetMainBagRep2D(BagRep2D* iBagRep2D) {
		m_pMainBagRep2D = iBagRep2D;
	}
	void AddBagRep2D(BagRep2D* iBagRep2D);
	void RemoveBagRep2D(BagRep2D* iBagRep2D);

private:
	vector<BagRep2D*> m_pBagRep2Ds;
	BagRep2D* m_pMainBagRep2D;
};

