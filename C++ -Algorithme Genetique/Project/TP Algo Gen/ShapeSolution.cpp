
#include "ShapeSolution.h"


ShapeSolution::ShapeSolution(Canvas const & canvas)
	:mCanvas{ canvas }, mShape{ nullptr }
{
}

void ShapeSolution::draw(windows_console::image & img) const
{
	mShape->draw(img);
}

void ShapeSolution::processFitness()
{
	mFitness = Solution::fitness();
}

bool ShapeSolution::isInsideCanvas() const
{
	return mCanvas.rectangle().contains(mShape->boundingRect());
}

bool ShapeSolution::isObstaclesIntersect() const
{
	for (auto const & obstacle : mCanvas.obstacles())
	{
		if (mShape->contains(obstacle))
		{
			return true;
		}
	}
	return false;
}
