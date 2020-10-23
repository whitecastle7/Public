
#include "SelectionRouletteWheel.h"


void SelectionRouletteWheel::prepare(Population const & population)
{
	size_t size{ population.size() };
	fitness_t totalFitness{ 0 };

	mRankWeight.resize(size);

	for (size_t i{ 0 }; i < size; ++i)
	{
		totalFitness += population[i].fitness();
	}

	if (totalFitness != 0)
	{
		mIsFitnessValid = true;
		double newFitness = double(population[0].fitness()) / double(totalFitness);
		mRankWeight[0] = newFitness;

		for (size_t i{ 1 }; i < size - 1; ++i)
		{
			newFitness = double(population[i].fitness()) / double(totalFitness);
			mRankWeight[i] = newFitness + mRankWeight[i - 1];
		}
		mRankWeight[size - 1] = 1.0;
	}
	else
	{
		mIsFitnessValid = false;
	}
}

Solution const & SelectionRouletteWheel::select(Population const & population)
{
	if (mIsFitnessValid)
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_real_distribution<double> unif(0.0, 1.0);
		//std::default_random_engine re;
		double percent = unif(mt);

		for (size_t i{ 1 }; i < population.size(); ++i)
		{
			if (percent < mRankWeight[i])
			{
				return population[i - 1];
			}
		}
	}
	else
	{
		std::random_device rd;
		std::mt19937 nt(rd());
		std::uniform_int_distribution<size_t> unif(0, population.size() - 1);
		//std::default_random_engine re;
		size_t index = unif(nt);

		return population[index];
	}

	return population[population.size() - 1];
}
