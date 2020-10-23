#pragma once

#ifndef SHAPE_OPTIMIZER_H
#define SHAPE_OPTIMIZER_H

#include "Canvas.h"
#include "Rectangle.h"
#include "GAParameters.h"
#include "GAEngine.h"
#include "ShapeSolution.h"
#include "console.h"
#include "CircleSolution.h"
#include "RectangleSolution.h"
#include "PolygonSolution.h"


class ShapeOptimizer
{
public:
	ShapeOptimizer();
	~ShapeOptimizer() = default;

	class ShapeObserver : public GAEngine::EvolutionObserver
	{
	public:
		ShapeObserver(ShapeOptimizer & so);
		~ShapeObserver() = default;

		void update(GAEngine const & engine) override;

	private:
		ShapeOptimizer & mShapeOptimizer;

	};

	void run();

private:
	bool allIsValid() const;
	void setup();
	void setConsole();
	void incrementShapeIndex();
	void setShape();
	void update(GAEngine const & engine);
	void display(GAEngine const & engine);
	void incrementColor();
	void setDrawColorDark(windows_console::image & img) const;
	void setDrawColorBright(windows_console::image & img) const;
	void setDrawColorObs(windows_console::image & img) const;
	void setDrawColorBackground(windows_console::image & img) const;
	void incrementAffichage();
	void showMenu();


	GAEngine mEngine;
	GAParameters mParameters;
	Canvas mCanvas;
	ShapeObserver mObserver;

	bool isInSelectionMenu{ true };
	bool isTimeToEvolve{ true };
	windows_console::console_events mCE;

	size_t mColorIndex{ 1 };
	size_t mMaxColorIndex{ 8 };

	//
	enum solutionType
	{
		circle = 0,
		rectangle = 1,
		polygon = 2
	};
	solutionType mSolType{ circle };

	enum affichage
	{
		none = 0,
		best = 1,
		all = 2
	};
	affichage mAffichage{ all };

};

#endif // SHAPE_OPTIMIZER_H