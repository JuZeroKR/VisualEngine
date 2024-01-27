#pragma once
// #include "OGV2DPoint.h"

class OGV2DLine
{
public:
	OGV2DLine(float startX, float startY, float endX, float endY);
	//OGV2DLine(OGV2DPoint i_spt, OGV2DPoint i_ept);
	~OGV2DLine();

	float m_startX;
	float m_startY;

	float m_endX;
	float m_endY;
};

