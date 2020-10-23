#pragma once

#ifndef SHAPE_H
#define SHAPE_H

#include "Rectangle.h"
#include "Point.h"
#include "console.h"


class Shape
{
public:
	Shape() = default;
	~Shape() = default;

	virtual bool isValid() const = 0;
	virtual void draw(windows_console::image & im) const = 0;
	virtual double area() const = 0;
	virtual Rectangle boundingRect() const = 0;
	virtual bool contains(Point const & p) const = 0;
	virtual Shape* clone() const = 0;

};

#endif // SHAPE_H