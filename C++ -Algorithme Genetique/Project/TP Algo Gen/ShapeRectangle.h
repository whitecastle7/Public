#pragma once


#ifndef SHAPE_RECTANGLE_H
#define SHAPE_RECTANGLE_H

#include "Shape.h" // required for Rectangle, Point, Console
#include "Point.h"
#include "console.h"


class ShapeRectangle :	public Shape,
						public Rectangle
{
public:
	ShapeRectangle();
	~ShapeRectangle() = default;

	bool isValid() const override;
	void draw(windows_console::image & img) const override;
	double area() const override;
	Rectangle boundingRect() const override;
	bool contains(Point const & p) const override;
	Shape* clone() const override;

};

#endif // SHAPE_RECTANGLE_H