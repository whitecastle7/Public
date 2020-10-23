
#include "RectangleSolution.h"
#include <cmath> // required for log


RectangleSolution::RectangleSolution(Canvas const & canvas)
	:ShapeSolution(canvas)
{
	mShape = &mRectangle;

	canvasWidth = mCanvas.rectangle().size().width();
	canvasHeight = mCanvas.rectangle().size().height();

	nbBitsLargeurCanvasX = static_cast<size_t>(ceil(log(canvasWidth) / log(2)));
	nbBitsHauteurCanvasY = static_cast<size_t>(ceil(log(canvasHeight) / log(2)));
	nbBitsLargeurRect = static_cast<size_t>(nbBitsLargeurCanvasX);
	nbBitsHauteurRect = static_cast<size_t>(nbBitsHauteurCanvasY);

	nbTotalBitsAEncoder = static_cast <int>(2 * nbBitsLargeurCanvasX + 2 * nbBitsHauteurCanvasY);

	mChromosome.resize(nbTotalBitsAEncoder);
}

void RectangleSolution::randomize() {

	mChromosome.randomize();
}

void RectangleSolution::encode() {

	// Bits pour le topLeftX de notre rectangle
	mChromosome.write(static_cast<size_t>(mRectangle.topLeft().x()), 0, nbBitsLargeurCanvasX);
	// Bits pour le topLeftY de notre rectangle
	mChromosome.write(static_cast<size_t>(mRectangle.topLeft().y()), nbBitsLargeurCanvasX, nbBitsHauteurCanvasY);

	// Bits pour la largeur de notre rectangle
	mChromosome.write(static_cast<size_t>(mRectangle.size().width()), nbBitsLargeurCanvasX + nbBitsHauteurCanvasY, nbBitsLargeurRect);
	// Bits pour la hauteur de notre rectangle
	mChromosome.write(static_cast<size_t>(mRectangle.size().height()), nbBitsLargeurCanvasX + nbBitsHauteurCanvasY + nbBitsLargeurRect, nbBitsHauteurRect);

}

void RectangleSolution::decode() {

	size_t topLeftX{};
	size_t topLeftY{};
	size_t width{};
	size_t height{};

	//Lire bits pour le x
	mChromosome.read(topLeftX, 0, nbBitsLargeurCanvasX);
	//Lire bits pour le y
	mChromosome.read(topLeftY, nbBitsLargeurCanvasX, nbBitsHauteurCanvasY);
	//Lire bits pour la largeur
	mChromosome.read(width, nbBitsLargeurCanvasX + nbBitsHauteurCanvasY, nbBitsLargeurRect);
	//Lire bits pour la hauteur
	mChromosome.read(height, nbBitsLargeurCanvasX + nbBitsHauteurCanvasY + nbBitsLargeurRect, nbBitsHauteurRect);

	Point pTopL{ static_cast<double>(topLeftX), static_cast<double>(topLeftY) };
	Point pTopR{ static_cast<double>(topLeftX + width), static_cast<double>(topLeftY + height) };

	mRectangle.set(pTopL, pTopR);


}

RectangleSolution * RectangleSolution::clone() const {

	RectangleSolution* temp{ new RectangleSolution(mCanvas) };
	temp->copy(*this);
	return temp;
}

void RectangleSolution::copy(Solution const & from) {

	mRectangle = static_cast<RectangleSolution const &>(from).mRectangle;
	Solution::copy(from);
}
