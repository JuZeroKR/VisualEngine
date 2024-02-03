#pragma once
#include "OGV2DPoint.h"
#include "OGV2DLine.h"
#include <vector>
using namespace std;

class OGV2DBeizerCurve
{
public:
	OGV2DBeizerCurve();
	OGV2DBeizerCurve(float startX, float startY, float midX, float midY, float endX, float endY);
	~OGV2DBeizerCurve();

	vector<OGV2DPoint> mPoints;
	vector<OGV2DLine> mLines;

	float m_startX;
	float m_startY;

	float m_midX;
	float m_midY;

	float m_endX;
	float m_endY;
};

