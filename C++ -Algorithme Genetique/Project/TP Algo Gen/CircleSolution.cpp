
#include "CircleSolution.h"
#include <cmath> // required for log


CircleSolution::CircleSolution(Canvas const & canvas)
	:ShapeSolution(canvas)
{
	mShape = &mCircle;

	width = mCanvas.rectangle().size().width();
	height = mCanvas.rectangle().size().height();

	nbBitsX = static_cast<size_t>(ceil(log(width) / log(2)));
	nbBitsY = static_cast<size_t>(ceil(log(height) / log(2)));
	nbBitsRadius = static_cast<size_t>(ceil(log(height / 2) / log(2)));

	nbTotalBitsAEncoder = static_cast<int>(nbBitsX + nbBitsY + nbBitsRadius);

	mChromosome.resize(nbTotalBitsAEncoder);
}


void CircleSolution::randomize() {

	mChromosome.randomize();
}

void CircleSolution::encode()
{
	// Bits pour le x
	mChromosome.write(static_cast<size_t>(mCircle.center().x()), 0, nbBitsX);
	// Bits pour le y
	mChromosome.write(static_cast<size_t>(mCircle.center().y()), nbBitsX, nbBitsY);
	// Bits pour le radius
	mChromosome.write(static_cast<size_t>(mCircle.radius()), nbBitsX + nbBitsY, nbBitsRadius);
}

void CircleSolution::decode()
{
	size_t x{};
	size_t y{};
	size_t r{};

	//Lire bits pour le x
	mChromosome.read(x, 0, nbBitsX);
	//Lire bits pour le y
	mChromosome.read(y, nbBitsX, nbBitsY);
	//Lire bits pour le radius
	mChromosome.read(r, nbBitsX + nbBitsY, nbBitsRadius);

	Point p{ static_cast<double>(x), static_cast<double>(y) };
	mCircle.set(p, static_cast<double>(r));
}

CircleSolution * CircleSolution::clone() const
{
	CircleSolution* temp{ new CircleSolution(mCanvas) };
	temp->copy(*this);
	return temp;
}

void CircleSolution::copy(Solution const & from)
{
	mCircle = static_cast<CircleSolution const &>(from).mCircle;
	Solution::copy(from);
}
