#include "pch.h"
#include "PolynomialOperation.h"

OGV2DPoint PolynomialOperation::GetPointOnLine(const OGV2DPoint& i_StartPt, const OGV2DPoint& i_EndPt, const double ratio)
{
	float x_StartPT = i_StartPt.x;
	float x_EndPT = i_EndPt.x;

	float x_Pt = (x_StartPT + x_EndPT) * ratio;

	float sleep = (i_EndPt.y - i_StartPt.y) / (i_EndPt.x - i_StartPt.x);
	float y;
	float x;
	float b = i_StartPt.y - sleep * i_StartPt.x;

	float y_Pt = sleep * x_Pt + b;


	return OGV2DPoint(x_Pt, y_Pt);
}

OGV2DPoint PolynomialOperation::GetPointOnLine(const float x1, const float y1, const float x2, const float y2, const double ratio)
{
	float x_Pt = (x1 + x2) * ratio;

	float sleep = (y2 - y1) / (x2 - x1);
	float y;
	float x;
	float b = y1 - sleep * x1;

	float y_Pt = sleep * x_Pt + b;

	return OGV2DPoint(x_Pt, y_Pt);
}


void PolynomialOperation::GetPointsBezierCurve(OGV2DPoint pt1, OGV2DPoint pt2, OGV2DPoint pt3, vector<OGV2DLine*>& i_lines, int interval)
{
	float _interval;
	
	

	float step = 1.0 / interval;
	float curStep = 0.0;
	for (int i = 1; i < interval; i++)
	{
		OGV2DPoint point = GetPointOnLine(pt1, pt2, curStep + step * i);
		pointsPt1Pt2.push_back(point);
	}

	for (int i = 1; i < interval; i++)
	{
		OGV2DPoint point = GetPointOnLine(pt2, pt3, curStep + step * i);
		pointsPt2Pt3.push_back(point);
	}

	for (int i = 0; i < pointsPt1Pt2.size(); i++)
	{
		OGV2DLine* line = new OGV2DLine(pointsPt1Pt2[i].GetX(), pointsPt1Pt2[i].GetY(), pointsPt2Pt3[pointsPt1Pt2.size()-i-1].GetX(), pointsPt2Pt3[pointsPt1Pt2.size()-i-1].GetY());
		i_lines.push_back(line);
	}
		

}
