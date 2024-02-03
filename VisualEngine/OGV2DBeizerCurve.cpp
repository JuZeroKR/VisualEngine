#include "pch.h"
#include "OGV2DBeizerCurve.h"
#include "PolynomialOperation.h"

OGV2DBeizerCurve::OGV2DBeizerCurve()
{
}

OGV2DBeizerCurve::OGV2DBeizerCurve(float startX, float startY, float midX, float midY, float endX, float endY)
{
	OGV2DPoint pt1 = OGV2DPoint(startX, startY);
	OGV2DPoint pt2 = OGV2DPoint(midX, midY);
	OGV2DPoint pt3 = OGV2DPoint(endX, endY);

	PolynomialOperation* polynomialOp = new PolynomialOperation();

	
	polynomialOp->GetPointsBezierCurve(pt1, pt2, pt3, mPoints, mLines,10);

	delete polynomialOp;
}

OGV2DBeizerCurve::~OGV2DBeizerCurve()
{
}
