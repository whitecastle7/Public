#pragma once

#ifndef SHAPE_SOLUTION_H
#define SHAPE_SOLUTION_H

#include "Canvas.h"
#include "Shape.h"
#include "Solution.h"
#include "console.h"


class ShapeSolution : public Solution
{
public:
	ShapeSolution(Canvas const & canvas);
	~ShapeSolution() = default;

	void draw(windows_console::image & img) const;
	void processFitness() override;
	bool isInsideCanvas() const;
	bool isObstaclesIntersect() const;

protected:
	Canvas const & mCanvas;
	Shape* mShape;

};

#endif // SHAPE_SOLUTION_H