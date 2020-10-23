#define _USE_MATH_DEFINES // required for PI
#include <cmath> // required for PI

#include "ShapeCircle.h"
#include "Rectangle.h" // required for Rectangle
#include "console.h" // required for csl

using namespace windows_console;


bool ShapeCircle::isValid() const
{
	return mRadius > 0;
}

Point ShapeCircle::center() const
{
	return mCenter;
}

double ShapeCircle::radius() const
{
	return mRadius;
}

void ShapeCircle::setRadius(double radius)
{
	mRadius = radius;
}

void ShapeCircle::set(Point const & center, double radius)
{
	mCenter = center;
	mRadius = radius;
}

void ShapeCircle::draw(windows_console::image & im) const
{
	im << circle(static_cast<image_manipulator::coordinate_type>(mCenter.x()),
		static_cast<image_manipulator::coordinate_type>(mCenter.y()),
		static_cast<image_manipulator::coordinate_type>(mRadius)); // couleurs traitees dans ShapeOptimizer
}

double ShapeCircle::area() const
{
	return mRadius * M_PI;
}

//Calcule le rectangle contenant le cercle
Rectangle ShapeCircle::boundingRect() const
{
	return Rectangle(mCenter.x() - mRadius, mCenter.y() - mRadius,
		mRadius * 2, mRadius * 2);
}

//Calcule si un point est a l'interieur du cercle
bool ShapeCircle::contains(Point const & p) const
{
	return mCenter.distance(p) > mRadius;
}

Shape* ShapeCircle::clone() const
{
	return new ShapeCircle(*this); // A CONFIRMER
}
