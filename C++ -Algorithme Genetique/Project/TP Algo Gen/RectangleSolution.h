#pragma once

#ifndef RECTANGLE_SOLUTION_H
#define RECTANGLE_SOLUTION_H

#include "ShapeSolution.h"
#include "ShapeRectangle.h"


class RectangleSolution : public ShapeSolution {
public:
	//RectangleSolution();
	RectangleSolution(Canvas const & canvas);
	~RectangleSolution() = default;

	void randomize() override;
	void encode() override;
	void decode() override;
	void copy(Solution const & from) override;
	RectangleSolution* clone() const override;

private:
	ShapeRectangle mRectangle;

	//for encode/decode
	double canvasWidth;
	double canvasHeight;
	size_t nbBitsLargeurCanvasX;
	size_t nbBitsHauteurCanvasY;
	size_t nbBitsLargeurRect;
	size_t nbBitsHauteurRect;


	int nbTotalBitsAEncoder;

};

#endif // RECTANGLE_SOLUTION_H