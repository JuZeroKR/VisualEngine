#pragma once

#include "OGV2DPoint.h"
#include "OGV2DLine.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
#include "OGVVisu.h"

class PolynomialOperation
{
public:
	vector<OGV2DPoint> pointsPt1Pt2;
	vector<OGV2DPoint> pointsPt2Pt3;

public:
	// return : OGV2DPoint
	OGV2DPoint GetPointOnLine(const OGV2DPoint& i_StartPt, const OGV2DPoint& i_EndPt, const double ratio);

	OGV2DPoint GetPointOnLine(const float x1, const float y1, const float x2, const float y2, const double ratio);

	OGV2DPoint GetPointOnLine(const OGV2DLine i_line, const double ratio);

	void GetPointsBezierCurve(OGV2DPoint pt1, OGV2DPoint pt2, OGV2DPoint pt3, vector<OGV2DLine*>& i_lines, int interval = 10);
	void GetPointsBezierCurve(OGV2DPoint pt1, OGV2DPoint pt2, OGV2DPoint pt3, vector<OGV2DPoint>& i_point, int interval = 10);
	void GetPointsBezierCurve(OGV2DPoint pt1, OGV2DPoint pt2, OGV2DPoint pt3, vector<OGV2DPoint>& i_point, vector<OGV2DLine>& i_lines,int interval = 10);

};

