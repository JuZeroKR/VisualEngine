#include "pch.h"
#include "OGV2DLine.h"

OGV2DLine::OGV2DLine(OGV2DPoint* i_spt, OGV2DPoint* i_ept)
{
	m_startPt = i_spt;
	m_endPt = i_ept;
}

OGV2DLine::~OGV2DLine()
{
}

float OGV2DLine::GetLength()
{
	return sqrt((m_startPt->GetX() - m_endPt->GetX()) * (m_startPt->GetX() - m_endPt->GetX()) -
				(m_startPt->GetY() - m_endPt->GetY()) * (m_startPt->GetY() - m_endPt->GetY()));
}
