
#include "EvolutionEngine.h"


size_t EvolutionEngine::currentGeneration() const
{
	return mCurrentGeneration;
}

Population const & EvolutionEngine::population() const
{
	return mPopulationEngine.population();
}

FitnessStatisticsOverTime const & EvolutionEngine::fitnessStatistics() const
{
	return mFitnessStatisticsOverEpoch;
}

void EvolutionEngine::setup(GAParameters & parameters)
{
	mPopulationEngine.setup(parameters);
}

void EvolutionEngine::evolveOneGeneration(GAParameters & parameters)
{
	mPopulationEngine.evolveOneGeneration(parameters);
}
