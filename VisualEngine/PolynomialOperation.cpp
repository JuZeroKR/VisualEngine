#include "pch.h"
#include "PolynomialOperation.h"

OGV2DPoint PolynomialOperation::GetPointOnLine(const OGV2DPoint& i_StartPt, const OGV2DPoint& i_EndPt, const double ratio)
{
	float x_StartPT = i_StartPt.x;
	float x_EndPT = i_EndPt.x;

	float x_Pt = x_StartPT + ((x_EndPT - x_StartPT) * ratio);

	float sleep = (i_EndPt.y - i_StartPt.y) / (i_EndPt.x - i_StartPt.x);
	float y;
	float x;
	float b = i_StartPt.y - sleep * i_StartPt.x;

	float y_Pt = sleep * x_Pt + b;

	cout << x_Pt << endl;

	return OGV2DPoint(x_Pt, y_Pt);
}

OGV2DPoint PolynomialOperation::GetPointOnLine(const float x1, const float y1, const float x2, const float y2, const double ratio)
{
	float x_StartPT = x1;
	float x_EndPT = x2;

	float x_Pt = x_StartPT + ((x_EndPT - x_StartPT) * ratio);

	float sleep = (y2 - y1) / (x2 - x1);
	float y;
	float x;
	float b = y1 - sleep * x1;

	float y_Pt = sleep * x_Pt + b;

	//cout << x_Pt << endl;

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
		if (i != pointsPt1Pt2.size() - 1)
		{
			cout << "X : " << pointsPt1Pt2[i + 1].GetX() - pointsPt1Pt2[i].GetX() << endl;
			cout << "Y    : " << pointsPt1Pt2[i + 1].GetY() - pointsPt1Pt2[i].GetY() << endl;
		}

		if (i != pointsPt1Pt2.size() - 1)
		{
			cout << "X          : " << pointsPt2Pt3[i + 1].GetX() - pointsPt2Pt3[i].GetX() << endl;
			cout << "Y            : " << pointsPt2Pt3[i + 1].GetY() - pointsPt2Pt3[i].GetY() << endl;
		}
			
		OGV2DLine* line = new OGV2DLine(pointsPt1Pt2[i].GetX(), pointsPt1Pt2[i].GetY(), pointsPt2Pt3[pointsPt1Pt2.size()-i-1].GetX(), pointsPt2Pt3[pointsPt1Pt2.size()-i-1].GetY());
		i_lines.push_back(line);
	}
		

}

void PolynomialOperation::GetPointsBezierCurve(OGV2DPoint pt1, OGV2DPoint pt2, OGV2DPoint pt3, vector<OGV2DPoint>& i_point, int interval)
{
	float _interval;
	vector<OGV2DLine> lines;


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
		if (i != pointsPt1Pt2.size() - 1)
		{
			cout << "X : " << pointsPt1Pt2[i + 1].GetX() - pointsPt1Pt2[i].GetX() << endl;
			cout << "Y    : " << pointsPt1Pt2[i + 1].GetY() - pointsPt1Pt2[i].GetY() << endl;
		}

		if (i != pointsPt1Pt2.size() - 1)
		{
			cout << "X          : " << pointsPt2Pt3[i + 1].GetX() - pointsPt2Pt3[i].GetX() << endl;
			cout << "Y            : " << pointsPt2Pt3[i + 1].GetY() - pointsPt2Pt3[i].GetY() << endl;
		}

		OGV2DLine line = OGV2DLine(pointsPt1Pt2[i].GetX(), pointsPt1Pt2[i].GetY(), pointsPt2Pt3[i].GetX(), pointsPt2Pt3[i].GetY());
		lines.push_back(line);
	}

	i_point.push_back(pt1);

	for (int i = 0; i < lines.size(); i++)
	{
		OGV2DPoint pt = GetPointOnLine(lines[i].m_startX, lines[i].m_startY, lines[i].m_endX, lines[i].m_endY, 0.5);
		i_point.push_back(pt);
	}

	i_point.push_back(pt3);
}

void PolynomialOperation::GetPointsBezierCurve(OGV2DPoint pt1, OGV2DPoint pt2, OGV2DPoint pt3, vector<OGV2DPoint>& i_point, vector<OGV2DLine>& i_lines, int interval)
{
	float _interval;
	vector<OGV2DLine> lines;


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

	i_lines.push_back(OGV2DLine(pt1.GetX(), pt1.GetY(), pt2.GetX(), pt2.GetY()));

	for (int i = 0; i < pointsPt1Pt2.size(); i++)
	{
		if (i != pointsPt1Pt2.size() - 1)
		{
			cout << "X : " << pointsPt1Pt2[i + 1].GetX() - pointsPt1Pt2[i].GetX() << endl;
			cout << "Y    : " << pointsPt1Pt2[i + 1].GetY() - pointsPt1Pt2[i].GetY() << endl;
		}

		if (i != pointsPt1Pt2.size() - 1)
		{
			cout << "X          : " << pointsPt2Pt3[i + 1].GetX() - pointsPt2Pt3[i].GetX() << endl;
			cout << "Y            : " << pointsPt2Pt3[i + 1].GetY() - pointsPt2Pt3[i].GetY() << endl;
		}

		OGV2DLine line = OGV2DLine(pointsPt1Pt2[i].GetX(), pointsPt1Pt2[i].GetY(), pointsPt2Pt3[i].GetX(), pointsPt2Pt3[i].GetY());
		i_lines.push_back(line);
	}
	i_lines.push_back(OGV2DLine(pt2.GetX(), pt2.GetY(), pt3.GetX(), pt3.GetY()));

	i_point.push_back(pt1);

	for (int i = 0; i < i_lines.size(); i++)
	{
		OGV2DPoint pt = GetPointOnLine(i_lines[i].m_startX, i_lines[i].m_startY, i_lines[i].m_endX, i_lines[i].m_endY, step*i);
		i_point.push_back(pt);
	}

	i_point.push_back(pt3);

}
