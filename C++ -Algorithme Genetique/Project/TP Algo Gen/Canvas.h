#pragma once

#ifndef CANVAS_H
#define CANVAS_H

#include <vector>
#include <random>

#include "Point.h"
#include "Rectangle.h"
#include "Size.h"
#include "console.h"


class Canvas
{
public:
	Canvas() = default;
	~Canvas() = default;

	bool isValid() const;
	Rectangle const & rectangle() const;
	std::vector<Point> const & obstacles() const;
	void set(Rectangle const & rectangle, size_t obstacleCount);
	size_t obstaclesCount() const;
	void setObstacles(size_t obstacleCount);
	void randomizeObstacles();
	void drawBackground(windows_console::image & img) const;
	void drawObstacles(windows_console::image & img) const;

private:
	Rectangle mRect;
	std::vector<Point> mObstacles;

};

#endif // CANVAS_H