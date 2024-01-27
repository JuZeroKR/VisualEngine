#include "pch.h"
#include "OGV2DLine.h"

OGV2DLine::OGV2DLine(float startX, float startY, float endX, float endY)
{
	m_startX = startX;
	m_startY = startY;
	m_endX = endX;
	m_endY = endY;
}

OGV2DLine::~OGV2DLine()
{
}

//float OGV2DLine::GetLength()
//{
//	return sqrt((m_startPt->GetX() - m_endPt->GetX()) * (m_startPt->GetX() - m_endPt->GetX()) -
//				(m_startPt->GetY() - m_endPt->GetY()) * (m_startPt->GetY() - m_endPt->GetY()));
//}
