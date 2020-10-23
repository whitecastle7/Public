
#include "ShapeOptimizer.h"
#include <iostream>

using namespace std;


ShapeOptimizer::ShapeOptimizer()
	:mObserver{*this}
{
}


void ShapeOptimizer::run()
{
	isInSelectionMenu = true;

	showMenu();
	setup();
	setConsole();

	if (allIsValid())
	{
		mEngine.evolveUntilConvergence(mParameters);
	}
}

bool ShapeOptimizer::allIsValid() const
{
	return mCanvas.isValid() && mParameters.isValid();
}

void ShapeOptimizer::setup()
{
	mEngine.registerObserver(mObserver);

	mCanvas.set(Rectangle(0.0, 0.0, 300.0, 200.0), 50);

	mParameters.setToDefault();
	setShape();

	while (isInSelectionMenu)
	{
		mCE.read_events();
		while (mCE.key_events_count())
		{
			char c{ mCE.next_key_event().ascii_value() };
			cout << c;
			switch (c)
			{
			case ' ':
				isInSelectionMenu = false;
				break;
			case 'q':
			case 'Q':
				mCanvas.setObstacles(mCanvas.obstaclesCount() - 10);
				break;
			case 'w':
			case 'W':
				mCanvas.setObstacles(mCanvas.obstaclesCount() + 10);
				break;
			case 'e':
			case 'E':
				mCanvas.randomizeObstacles();
				break;
			case 'a':
			case 'A':
				incrementShapeIndex();
				setShape();
				break;
			case '1':
			case '2':
			case '3':
			case '4':
				mParameters.setConcurrentPopulationCount(c - '0');
				break;
			}
		}
		// draw menu initial ?
	}

}

void ShapeOptimizer::setConsole()
{
	using namespace windows_console;

	csl << key_events::add_filter<key_filter_up>;

	csl << window::title("B52")
		<< window::fit(300, 200, "Consolas", font::size_type{ 3 }, font::ratio_type{ 1.0 })
		<< window::unclosable
		<< window::unresizable
		<< window::center
		<< cursor::invisible;
}

void ShapeOptimizer::incrementShapeIndex()
{
	switch (mSolType)
	{
	case circle:
		mSolType = rectangle;
		break;
	case rectangle:
		mSolType = polygon;
		break;
	case polygon:
		mSolType = circle;
		break;
	}
}

void ShapeOptimizer::setShape()
{
	switch (mSolType)
	{
	case circle:
		mParameters.setSolutionSample(new CircleSolution(mCanvas));
		break;
	case rectangle:
		mParameters.setSolutionSample(new RectangleSolution(mCanvas));
		break;
	case polygon:
		mParameters.setSolutionSample(new PolygonSolution(mCanvas));
		break;
	}
}

void ShapeOptimizer::update(GAEngine const & engine)
{
	display(engine);

	mCE.read_events();

	while (mCE.key_events_count())
	{
		switch (mCE.next_key_event().ascii_value())
		{
		case 27:
			mEngine.stopEvolution();
			isTimeToEvolve = false;
			break;
		case ' ':
			incrementAffichage();
			break;
		}
	}
}

void ShapeOptimizer::display(GAEngine const & engine)
{
	using namespace windows_console;

	image img;

	setDrawColorBackground(img);
	mCanvas.drawBackground(img);

	img << no_brush;

	switch (mAffichage)
	{
	case none:
		break;
	case best:
		mColorIndex = 5;
		for (size_t p{ 0 }; p < mParameters.concurrentPopulationCount(); ++p)
		{
			setDrawColorBright(img);
			static_cast<ShapeSolution const &>(engine.population(p)[0]).draw(img);
			incrementColor();
		}
		break;
	case all:
		mColorIndex = 5;
		for (size_t p{ 0 }; p < mParameters.concurrentPopulationCount(); ++p)
		{
			setDrawColorDark(img);
			for (size_t i{ 1 }; i < engine.population(p).size(); ++i)
			{
				static_cast<ShapeSolution const &>(engine.population(p)[i]).draw(img);
			}
			setDrawColorBright(img);
			static_cast<ShapeSolution const &>(engine.population(p)[0]).draw(img);
			incrementColor();
		}
		break;
	}

	setDrawColorObs(img);
	mCanvas.drawObstacles(img);
	csl << img;
}

void ShapeOptimizer::incrementColor()
{
	if (mColorIndex >= mMaxColorIndex)
	{
		mColorIndex = 1;
	}
	else
	{
		++mColorIndex;
	}
}

void ShapeOptimizer::setDrawColorDark(windows_console::image & img) const
{
	using namespace windows_console;
	img << pen(dot, text_color(dark, static_cast<color_type>(mColorIndex)), background_color(dark, static_cast<color_type>(mColorIndex)));
}

void ShapeOptimizer::setDrawColorBright(windows_console::image & img) const
{
	using namespace windows_console;
	img << pen(dot, text_color(bright, static_cast<color_type>(mColorIndex)), background_color(bright, static_cast<color_type>(mColorIndex)));
}

void ShapeOptimizer::setDrawColorObs(windows_console::image & img) const
{
	using namespace windows_console;
	img << pen(dot, text_color(bright, white), background_color(bright, white));
}

void ShapeOptimizer::setDrawColorBackground(windows_console::image & img) const
{
	using namespace windows_console;
	//img << no_pen;
	img << pen(dot, text_color(dark, black), background_color(dark, black));
	img << brush(dot, text_color(dark, black), background_color(dark, black));
}

void ShapeOptimizer::incrementAffichage()
{
	switch (mAffichage)
	{
	case none:
		mAffichage = best;
		break;
	case best:
		mAffichage = all;
		break;
	case all:
		mAffichage = none;
		break;
	}
}


ShapeOptimizer::ShapeObserver::ShapeObserver(ShapeOptimizer & so)
	:mShapeOptimizer{ so }
{
}


void ShapeOptimizer::ShapeObserver::update(GAEngine const & engine)
{
	mShapeOptimizer.update(engine);
}



void ShapeOptimizer::showMenu() {
	using namespace windows_console;

	csl << key_events::add_filter<key_filter_up>;

	csl << window::title("B52 - Algorithme Genetique")
		<< window::fit(100, 50, "Consolas", font::size_type{ 16 }, font::ratio_type{ 0.5 })
		<< window::unclosable
		<< window::unresizable
		<< window::center
		<< cursor::invisible;

	image img;
	img << pen(dot, text_color(bright, red), background_color(dark, red))
		<< windows_console::circle(50, 50, 10);

	cout << endl;
	cout << "    _   _              _ _   _                                  _   _               " << endl;
	cout << "   /_\\ | |__ _ ___ _ _(_) |_| |_  _ __  ___   __ _ ___ _ _  ___| |_(_)__ _ _  _ ___ " << endl;
	cout << "  / _ \\| / _` / _ \\ '_| |  _| ' \\| '  \\/ -_) / _` / -_) ' \\/ -_)  _| / _` | || / -_)" << endl;
	cout << " /_/ \\_\\_\\__, \\___/_| |_|\\__|_||_|_|_|_\\___| \\__, \\___|_||_\\___|\\__|_\\__, |\\_,_\\___|" << endl;
	cout << "         |___/                               |___/                      |_|         " << endl;

	cout << "\n\n\n\n" << "----------------";
	cout << "\n\tOptions: ";
	cout << "\n\t\t'q'/'w'\t\tAugmente/Reduit le nombre d'obstacles";
	cout << "\n\t\t'e'\t\tReinitialise aleatoirement la position des obstacles";
	cout << "\n\t\t1-4\t\tDetermine le nombre de population courante";
	cout << "\n\t\t'a'\t\tBascule la forme geometrique (Cercle - Rectangle - Polygone)";
	cout << "\n\t\t'espace'\tDemarrer la resolution";
}
