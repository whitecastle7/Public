#pragma once

#ifndef CIRCLE_SOLUTION_H
#define CIRCLE_SOLUTION_H

#include "ShapeSolution.h"
#include "ShapeCircle.h" // Point est inclus dans ShapeCircle.h


class CircleSolution : public ShapeSolution {
public:
	//CircleSolution();
	CircleSolution(Canvas const & canvas);
	~CircleSolution() = default;

	void randomize() override;
	void encode() override;
	void decode() override;
	void copy(Solution const & from) override;
	CircleSolution* clone() const override;

private:
	ShapeCircle mCircle;

	//for encode/decode
	double width;
	double height;
	size_t nbBitsX;
	size_t nbBitsY;
	size_t nbBitsRadius;

};

#endif // CIRCLE_SOLUTION_H