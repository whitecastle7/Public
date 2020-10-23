
#include "GAEngine.h"


size_t GAEngine::currentGeneration() const
{
	return mEvolutionEngine[0].currentGeneration();
}

Population const & GAEngine::population(size_t popIndex) const
{
	return mEvolutionEngine[popIndex].population();
}

FitnessStatisticsOverTime const & GAEngine::fitnessStatistics(size_t popIndex) const
{
	return mEvolutionEngine[popIndex].fitnessStatistics();
}

void GAEngine::evolveUntilConvergence(GAParameters & parameters)
{
	//
	if (mEvolutionStatus != InProcess)
	{
		mEvolutionStatus = InProcess;
		mEvolutionEngine.resize(parameters.concurrentPopulationCount());

		for (EvolutionEngine & evoEng : mEvolutionEngine)
		{
			evoEng.setup(parameters);
		}

		while (currentGeneration() < parameters.maximumGenerationCount() && mEvolutionStatus == InProcess)
		{
			for (EvolutionEngine & evoEng : mEvolutionEngine)
			{
				evoEng.evolveOneGeneration(parameters);
			}
			updateObservers();
		}
		mEvolutionStatus = SolutionAvailable;
	}
}

void GAEngine::stopEvolution()
{
	mEvolutionStatus = SolutionAvailable;
}

void GAEngine::registerObserver(EvolutionObserver & obs)
{
	using namespace std;

	list<EvolutionObserver*>::iterator it = find(mObservers.begin(), mObservers.end(), & obs);

	if (it == mObservers.end())
	{
		mObservers.push_back(& obs);
	}
}

void GAEngine::unregisterObserver(EvolutionObserver & obs)
{
	mObservers.remove(& obs);
}

void GAEngine::unregisterObserver()
{
	mObservers.clear();
}

void GAEngine::updateObservers()
{
	for (EvolutionObserver* & obs : mObservers)
	{
		obs->update(*this);
	}
}
