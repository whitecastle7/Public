#pragma once

#ifndef SHAPE_CIRCLE_H
#define SHAPE_CIRCLE_H

#include "Shape.h" // required for Rectangle
#include "Point.h" // required for Point
#include "console.h" // required for windows_console


class ShapeCircle : public Shape
{
public:
	ShapeCircle() = default;
	~ShapeCircle() = default;

	Point center() const;
	double radius() const;
	void setRadius(double radius);
	void set(Point const & center, double radius);

	bool isValid() const override;
	void draw(windows_console::image & im) const override; // revoir les param
	double area() const override;
	Rectangle boundingRect() const override;
	bool contains(Point const & p) const override;
	Shape* clone() const override;

private:
	Point mCenter;
	double mRadius{};

};

#endif // SHAPE_CIRCLE_H