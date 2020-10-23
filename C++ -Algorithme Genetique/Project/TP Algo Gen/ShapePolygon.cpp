
#include "ShapePolygon.h"

//Polygon choisi : le diamand

using namespace bg;
using namespace windows_console;


ShapePolygon::ShapePolygon()
{
	mPolygon.buildDiamond(mHalfWidth, mHalfHeight, mCenter, mOrientationDegrees);
}


bool ShapePolygon::isValid() const
{
	return mPolygon.isValid();
}

Point ShapePolygon::center() const
{
	return mCenter;
}

double ShapePolygon::halfWidth() const
{
	return mHalfWidth;
}

double ShapePolygon::halfHeight() const
{
	return mHalfHeight;
}

double ShapePolygon::rotation() const
{
	return mOrientationDegrees;
}

void ShapePolygon::setEverything(Point center, double halfWidth, double halfHeight, double degrees)
{
	mCenter = center;
	mHalfWidth = halfWidth;
	mHalfHeight = halfHeight;
	mOrientationDegrees = degrees;
}

void ShapePolygon::draw(windows_console::image & img) const
{
	// WHAT IS THIS
	// using WTF = static_cast<windows_console::image_manipulator::coordinate_type>;
	img << line(static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[0].x()),
		static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[0].y()),
		static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[1].x()),
		static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[1].y()))
		<< line(static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[1].x()),
			static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[1].y()),
			static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[2].x()),
			static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[2].y()))
		<< line(static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[2].x()),
			static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[2].y()),
			static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[3].x()),
			static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[3].y()))
		<< line(static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[3].x()),
			static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[3].y()),
			static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[1].x()),
			static_cast<windows_console::image_manipulator::coordinate_type>(mPolygon[1].y()));
}

double ShapePolygon::area() const
{
	return mPolygon.area();
}

Rectangle ShapePolygon::boundingRect() const
{
	return mPolygon.boundingBox();
}

bool ShapePolygon::contains(Point const & p) const
{
	return mPolygon.contained(p);
}

Shape * ShapePolygon::clone() const
{
	return new ShapePolygon(*this);
}
