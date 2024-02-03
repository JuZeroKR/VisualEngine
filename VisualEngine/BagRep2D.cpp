#include "pch.h"
#include "BagRep2D.h"

BagRep2D::BagRep2D()
{

}

BagRep2D::~BagRep2D()
{

}

void BagRep2D::Empty()
{
	for (int i = 0; i < m_pPoints.size(); i++)
	{
		delete m_pPoints[i];
	}

	for (int i = 0; i < m_pLines.size(); i++)
	{
		delete m_pLines[i];
	}

	m_pPoints.clear();
	m_pLines.clear();
	m_pBeizerCurves.clear();
}

void BagRep2D::AddPoint(OGV2DPoint* iPoint)
{
	m_pPoints.push_back(iPoint);
}

void BagRep2D::AddLine(OGV2DLine* iLine)
{
	m_pLines.push_back(iLine);
}

void BagRep2D::AddBeizerCurve(OGV2DBeizerCurve* iBeizerCurve)
{
	m_pBeizerCurves.push_back(iBeizerCurve);
}

void BagRep2D::RemovePoint(OGV2DPoint* iPoint)
{
	for (int i = 0; i < m_pPoints.size(); i++)
	{
		if (iPoint == m_pPoints[i])
		{
			m_pPoints.erase(m_pPoints.begin() + i);
			break;
		}
	}
}

void BagRep2D::RemoveLine(OGV2DLine* iLine)
{
	for (int i = 0; i < m_pLines.size(); i++)
	{
		if (iLine == m_pLines[i])
		{
			m_pLines.erase(m_pLines.begin() + i);
			break;
		}
	}
}
