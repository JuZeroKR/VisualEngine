#pragma once
#include "OGVMathematics.h"

class OGVMathVector2D
{
public:
	OGVMathVector2D();
	OGVMathVector2D(double iX, double iY);
	
	// Getter
	double GetX();
	double GetY();

	double Norm();
	// Normailzae
	void Normalize();
	// Innder Product

	// Length

	// Distance
	double DistanceTo(OGVMathVector2D& vec2D);

	// Cross Product

	// AngleTo (radians)
	double AngleTo(OGVMathVector2D& vec2D);
	OGVMathVector2D operator+(OGVMathVector2D& vec2D);
	OGVMathVector2D operator-(OGVMathVector2D& vec2D);
	double operator*(OGVMathVector2D& vec2D);

private:
	double m_X, m_Y;
};

