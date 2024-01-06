#pragma once
#include "OGV2DPoint.h"

class OGV2DLine
{
public:
	OGV2DLine(OGV2DPoint* i_spt, OGV2DPoint* i_ept);
	~OGV2DLine();

	OGV2DPoint* m_endPt;
	OGV2DPoint* m_startPt;

	float GetLength();

};

