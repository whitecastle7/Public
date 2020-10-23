
#include "ShapeRectangle.h"

using namespace windows_console;


ShapeRectangle::ShapeRectangle()
{
}


bool ShapeRectangle::isValid() const
{
	return Rectangle::isValid();
}

void ShapeRectangle::draw(windows_console::image & img) const
{
	img << rectangle(static_cast<image_manipulator::coordinate_type>(topLeft().x()),
		static_cast<image_manipulator::coordinate_type>(topLeft().y()),
		static_cast<image_manipulator::coordinate_type>(size().width()),
		static_cast<image_manipulator::coordinate_type>(size().height()));
}

double ShapeRectangle::area() const
{
	return Rectangle::area();
}

Rectangle ShapeRectangle::boundingRect() const
{
	return *this;
}

bool ShapeRectangle::contains(Point const & p) const
{
	return Rectangle::contains(p);
}

Shape* ShapeRectangle::clone() const
{
	return new ShapeRectangle(*this);
}
