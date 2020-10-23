#pragma once

//Polygon choisi : le diamand

#ifndef SHAPE_POLYGON_H
#define SHAPE_POLYGON_H

#include "Shape.h" // required for Rectangle, Point, Console
#include "Polygon2d.h" // Required for bg::Polygon2d
#include "Point2d.h" // required for Point2d


class ShapePolygon : public Shape
{
public:
	ShapePolygon();
	~ShapePolygon() = default;

	bool isValid() const override;
	Point center() const;
	double halfWidth() const;
	double halfHeight() const;
	double rotation() const;
	void setEverything(Point center, double halfWidth, double halfHeight, double degrees);

	void draw(windows_console::image & img) const override;
	double area() const override;
	Rectangle boundingRect() const override;
	bool contains(Point const & p) const override;
	Shape* clone() const override;

private:
	bg::Polygon2d mPolygon;

	double mHalfWidth;
	double mHalfHeight;
	bg::Point2d mCenter;
	double mOrientationDegrees;

};

#endif // SHAPE_POLYGON_H