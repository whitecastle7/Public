
#include "Canvas.h"

using namespace windows_console;


bool Canvas::isValid() const
{
	return mRect.isValid();
}

Rectangle const & Canvas::rectangle() const
{
	return mRect;
}

std::vector<Point> const & Canvas::obstacles() const
{
	return mObstacles;
}

void Canvas::set(Rectangle const & rectangle, size_t obstacleCount)
{
	mRect = rectangle;
	setObstacles(obstacleCount);
}

size_t Canvas::obstaclesCount() const
{
	return mObstacles.size();
}

void Canvas::setObstacles(size_t obstacleCount)
{	
	if (obstacleCount > 0)
	{
		mObstacles.resize(obstacleCount);
		randomizeObstacles();
	}
}

void Canvas::randomizeObstacles()
{
	std::uniform_real_distribution<double> randX(0.0, mRect.size().width() - 1);
	std::uniform_real_distribution<double> randY(0.0, mRect.size().height() - 1);
	std::default_random_engine re;

	for (Point & obs : mObstacles)
	{
		obs.set(randX(re), randY(re));
	}
}

void Canvas::drawBackground(windows_console::image & img) const
{
	img << windows_console::rectangle(static_cast<windows_console::image_manipulator::coordinate_type>(mRect.topLeft().x()),
		static_cast<windows_console::image_manipulator::coordinate_type>(mRect.topLeft().y()),
		static_cast<windows_console::image_manipulator::coordinate_type>(mRect.size().width()),
		static_cast<windows_console::image_manipulator::coordinate_type>(mRect.size().height()));
}

void Canvas::drawObstacles(windows_console::image & img) const
{
	for (Point const & p : mObstacles)
	{
		img << point(static_cast<windows_console::image_manipulator::coordinate_type>(p.x()), static_cast<windows_console::image_manipulator::coordinate_type>(p.y()));
	}
}
