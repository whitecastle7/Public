#pragma once

#ifndef POLYGON_SOLUTION_H
#define POLYGON_SOLUTION_H

#include "ShapeSolution.h"
#include "ShapePolygon.h"


class PolygonSolution : public ShapeSolution
{
public:
	//PolygonSolution();
	PolygonSolution(Canvas const & canvas);
	~PolygonSolution() = default;

	void randomize() override;
	void encode() override;
	void decode() override;
	void copy(Solution const & from) override;
	PolygonSolution* clone() const override;

private:
	ShapePolygon mPolygon;

	//for encode/decode
	double maxWidth;
	double maxHeight;

	size_t nbBitsCentreX;
	size_t nbBitsCentreY;
	size_t nbBitsHalfWidth;
	size_t nbBitsHalfHeight;
	size_t nbBitsRotation;

	int nbTotalBitsAEncoder;

};

#endif // POLYGON_SOLUTION_H