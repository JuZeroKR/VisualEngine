#include "pch.h"
#include "OGV2DPoint.h"

OGV2DPoint::OGV2DPoint()
{
}

OGV2DPoint::OGV2DPoint(float i_x, float i_y)
{
    x = i_x;
    y = i_y;
}

OGV2DPoint::~OGV2DPoint()
{
}

float OGV2DPoint::DistanceTo(OGV2DPoint& ipt)
{
    return sqrt((ipt.x - x)*(ipt.x - x) - (ipt.y - y)*(ipt.y - y));
}
