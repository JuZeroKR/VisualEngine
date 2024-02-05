#include "pch.h"
#include "OGVMathVector2D.h"

#include <cmath>

OGVMathVector2D::OGVMathVector2D()
{
    m_X = 0.0;
    m_Y = 0.0;
}

OGVMathVector2D::OGVMathVector2D(double iX, double iY)
{
    m_X = iX;
    m_Y = iY;
}

double OGVMathVector2D::GetX()
{
    return m_X;
}

double OGVMathVector2D::GetY()
{
    return m_Y;
}

double OGVMathVector2D::Norm()
{
    return sqrt(m_X*m_X + m_Y*m_Y);
}

void OGVMathVector2D::Normalize()
{
    m_X = m_X / Norm();
    m_Y = m_Y / Norm();
}

double OGVMathVector2D::DistanceTo(OGVMathVector2D& vec2D)
{
    return sqrt((vec2D.GetX()-m_X) * (vec2D.GetX() - m_X) +
        (vec2D.GetY() - m_Y) * (vec2D.GetY() - m_Y)
    );
}

double OGVMathVector2D::AngleTo(OGVMathVector2D& vec2D)
{
    double cosAngle = (m_X * vec2D.GetX()) + (m_Y * vec2D.GetY()) / (sqrt(m_X * m_X + m_Y * m_Y) * sqrt((vec2D.GetX() * vec2D.GetX()) + (vec2D.GetY() * vec2D.GetY())));
    return acos(cosAngle);
}

OGVMathVector2D OGVMathVector2D::operator+(OGVMathVector2D& vec2D)
{
    double x = m_X + vec2D.GetX();
    double y = m_Y + vec2D.GetY();

    return OGVMathVector2D(x, y);
}

OGVMathVector2D OGVMathVector2D::operator-(OGVMathVector2D& vec2D)
{
    double x = m_X - vec2D.GetX();
    double y = m_Y - vec2D.GetY();

    return OGVMathVector2D(x, y);
}

double OGVMathVector2D::operator*(OGVMathVector2D& vec2D)
{
    return (m_X * vec2D.GetX()) + (m_Y * vec2D.GetY());
}
