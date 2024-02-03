#pragma once
#include "OGV2DPoint.h"
#include "OGV2DLine.h"
#include "OGV2DBeizerCurve.h"

#include <vector>
using namespace std;

class BagRep2D
{
public:
	BagRep2D();
	~BagRep2D();
public:
	void Empty();
	void AddPoint(OGV2DPoint* iPoint);
	void AddLine(OGV2DLine* iLine);
	void AddBeizerCurve(OGV2DBeizerCurve* iBeizerCurve);


	void RemovePoint(OGV2DPoint* iPoint);
	void RemoveLine(OGV2DLine* iLine);
	void RemoveBeizerCurve(OGV2DBeizerCurve* iBeizerCurve);

	vector<OGV2DPoint*>& GetPoints()
	{
		return m_pPoints;
	}
	vector<OGV2DLine*>& GetLines()
	{
		return m_pLines;
	}
	vector<OGV2DBeizerCurve*>& GetBeizerCurves()
	{
		return m_pBeizerCurves;
	}

private:
	vector<OGV2DPoint*> m_pPoints;
	vector<OGV2DLine*> m_pLines;
	vector<OGV2DBeizerCurve*> m_pBeizerCurves;
};

