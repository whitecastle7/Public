
#include "PopulationEngine.h"


Population const & PopulationEngine::population() const
{
	return mPopulation;
}

FitnessStatistics const & PopulationEngine::fitnessStatistics() const
{
	return mFitnessStatistics;
}

void PopulationEngine::setup(GAParameters & parameters)
{
	mPopulation.set(parameters.populationSize(), parameters.solutionSample());
	mNextPopulation.set(parameters.populationSize(), parameters.solutionSample());
	mFitnessStatistics.reset();
	mNextPopulation.randomize();
	finalizeCurrentEvolution();
}

void PopulationEngine::evolveOneGeneration(GAParameters & parameters)
{
	parameters.selectionStrategy().prepare(mPopulation);
	processElitisme(parameters.ellitismSize());

	for (size_t i{ parameters.ellitismSize() }; i < mPopulation.size(); ++i)
	{
		processOneOffspring(parameters, i);
	}
	finalizeCurrentEvolution();
}

void PopulationEngine::processElitisme(size_t elitismSize)
{
	for (size_t i{ 0 }; i < elitismSize; ++i)
	{
		mNextPopulation[i].copy(mPopulation[i]);
	}
}

void PopulationEngine::processOneOffspring(GAParameters & parameters, size_t position)
{
	Solution const & g1 = parameters.selectionStrategy().select(mPopulation);
	Solution const & g2 = parameters.selectionStrategy().select(mPopulation);

	parameters.crossoverStrategy().breed(g1, g2, mNextPopulation[position]);
	parameters.mutationStrategy().mutate(mNextPopulation[position]);
}

void PopulationEngine::finalizeCurrentEvolution()
{
	mNextPopulation.decode();
	mNextPopulation.processFitness();
	mNextPopulation.sort();
	mPopulation.swap(mNextPopulation);
	processStatistics();
}

void PopulationEngine::processStatistics()
{
	mFitnessStatistics.count = mPopulation.size();
	for (size_t i{ 0 }; i < mFitnessStatistics.count; ++i)
	{
		mFitnessStatistics.average += mPopulation[i].fitness();
	}
	mFitnessStatistics.average /= mFitnessStatistics.count;
	mFitnessStatistics.maximum = mPopulation[0].fitness();
	mFitnessStatistics.minimum = mPopulation[mPopulation.size() - 1].fitness();
}
