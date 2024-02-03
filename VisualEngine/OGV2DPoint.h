#pragma once


class OGV2DPoint
{
public:
	OGV2DPoint();
	OGV2DPoint(float i_x, float i_y);
	~OGV2DPoint();

	float x;
	float y;

public:
	float GetX()
	{
		return x;
	};
	float GetY()
	{
		return y;
	};
	float DistanceTo(OGV2DPoint& ipt);


};

