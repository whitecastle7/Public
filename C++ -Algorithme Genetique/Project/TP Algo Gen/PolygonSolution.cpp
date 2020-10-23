
#include "PolygonSolution.h"


PolygonSolution::PolygonSolution(Canvas const & canvas)
	:ShapeSolution(canvas)
{
	mShape = &mPolygon;

	maxWidth = mCanvas.rectangle().size().width() / 2;
	maxHeight = mCanvas.rectangle().size().height() / 2;

	nbBitsCentreX = static_cast<size_t>(ceil(log(maxWidth) / log(2)));
	nbBitsCentreY = static_cast<size_t>(ceil(log(maxHeight) / log(2)));
	nbBitsHalfWidth = static_cast<size_t>(ceil(log(maxWidth / 2) / log(2)));
	nbBitsHalfHeight = static_cast<size_t>(ceil(log(maxHeight / 2) / log(2)));
	nbBitsRotation = static_cast<size_t>(ceil(log(360) / log(2)));

	nbTotalBitsAEncoder = static_cast<int>(nbBitsCentreX + nbBitsCentreY + +nbBitsHalfWidth + nbBitsHalfHeight + nbBitsRotation);

	mChromosome.resize(nbTotalBitsAEncoder);
}

void PolygonSolution::randomize() {

	mChromosome.randomize();
}

void PolygonSolution::encode() {

	// Bits pour le centreX
	mChromosome.write(static_cast<size_t>(mPolygon.center().x()), 0, nbBitsCentreX);
	// Bits pour le centreY
	mChromosome.write(static_cast<size_t>(mPolygon.center().y()), nbBitsCentreX, nbBitsCentreY);
	//Bits pour la mi-largeur
	mChromosome.write(static_cast<size_t>(mPolygon.halfWidth()), nbBitsCentreX + nbBitsCentreY, nbBitsHalfWidth);
	//Bits pour la mi-hauteur
	mChromosome.write(static_cast<size_t>(mPolygon.halfHeight()), nbBitsCentreX + nbBitsCentreY + nbBitsHalfWidth, nbBitsHalfHeight);
	// Bits pour la rotation
	mChromosome.write(static_cast<size_t>(mPolygon.rotation()), nbBitsCentreX + nbBitsCentreY + nbBitsHalfWidth + nbBitsHalfHeight, nbBitsRotation);
}

void PolygonSolution::decode() {

	size_t centreX{};
	size_t centreY{};
	size_t halfWidth{};
	size_t halfHeight{};
	size_t rotation{};

	//Lire bits pour le x
	mChromosome.read(centreX, 0, nbBitsCentreX);
	//Lire bits pour le y
	mChromosome.read(centreY, nbBitsCentreX, nbBitsCentreY);
	//Lire bits pour la mi-largeur
	mChromosome.read(halfWidth, nbBitsCentreX + nbBitsCentreY, nbBitsHalfWidth);
	//Lire bits pour la mi-hauteur
	mChromosome.read(halfHeight, nbBitsCentreX + nbBitsCentreY + nbBitsHalfWidth, nbBitsHalfHeight);
	//Lire bits pour la rotation
	mChromosome.read(rotation, nbBitsCentreX + nbBitsCentreY + nbBitsHalfWidth + nbBitsHalfHeight, nbBitsRotation);

	Point p{ static_cast<double>(centreX), static_cast<double>(centreY) };

	mPolygon.setEverything(p, static_cast<double>(halfWidth), static_cast<double>(halfHeight), static_cast<double>(rotation));
}

void PolygonSolution::copy(Solution const & from) {

	mPolygon = static_cast<PolygonSolution const &>(from).mPolygon;
	Solution::copy(from);
}

PolygonSolution * PolygonSolution::clone() const {

	PolygonSolution* temp{ new PolygonSolution(mCanvas) };
	temp->copy(*this);
	return temp;
}