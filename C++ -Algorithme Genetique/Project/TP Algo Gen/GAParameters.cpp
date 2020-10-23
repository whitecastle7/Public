
#include "GAParameters.h"


GAParameters::~GAParameters()
{
	delete mSolutionSample;
	mSolutionSample = nullptr;
	delete mSelectionStrategy;
	mSelectionStrategy = nullptr;
	delete mCrossoverStrategy;
	mCrossoverStrategy = nullptr;
	delete mMutationStrategy;
	mMutationStrategy = nullptr;
}


bool GAParameters::isValid() const
{
	if (mPopulationSize < 3 ||
		mEllitismSize < 0 ||
		mEllitismSize > mPopulationSize ||
		mConcurrentPopulationCount < 1 ||
		mConcurrentPopulationCount > 6 ||
		mMaximumGenerationCount < 3 ||
		mSolutionSample == nullptr || 
		mSelectionStrategy == nullptr || 
		mCrossoverStrategy == nullptr || 
		mMutationStrategy == nullptr)
	{
		return false;
	}
	return true;
}

size_t GAParameters::populationSize() const
{
	return mPopulationSize;
}

size_t GAParameters::ellitismSize() const
{
	return mEllitismSize;
}

size_t GAParameters::concurrentPopulationCount()
{
	return mConcurrentPopulationCount;
}

size_t GAParameters::maximumGenerationCount() const
{
	return mMaximumGenerationCount;
}

SelectionStrategy & GAParameters::selectionStrategy()
{
	return *mSelectionStrategy;
}

CrossoverStrategy & GAParameters::crossoverStrategy()
{
	return *mCrossoverStrategy;
}

MutationStrategy & GAParameters::mutationStrategy()
{
	return *mMutationStrategy;
}

Solution const & GAParameters::solutionSample() const
{
	return *mSolutionSample;
}

void GAParameters::setPopulationSize(size_t size)
{
	mPopulationSize = size;
}

void GAParameters::setEllitismSize(size_t size)
{
	mEllitismSize = size;
}

void GAParameters::setConcurrentPopulationCount(size_t count)
{
	mConcurrentPopulationCount = count;
}

void GAParameters::setMaximumGenerationCount(size_t count)
{
	mMaximumGenerationCount = count;
}

void GAParameters::setSelectionStrategy(SelectionStrategy * strategy)
{
	delete mSelectionStrategy;
	mSelectionStrategy = strategy;
}

void GAParameters::setCrossoverStrategy(CrossoverStrategy * strategy)
{
	delete mCrossoverStrategy;
	mCrossoverStrategy = strategy;
}

void GAParameters::setMutationStrategy(MutationStrategy * strategy)
{
	delete mMutationStrategy;
	mMutationStrategy = strategy;
}

void GAParameters::setSolutionSample(Solution * solution)
{
	delete mSolutionSample;
	mSolutionSample = solution;
}

void GAParameters::clearAll()
{
	setPopulationSize(0);
	setEllitismSize(0);
	setConcurrentPopulationCount(0);
	setMaximumGenerationCount(0);

	delete mSolutionSample;
	setSolutionSample(nullptr);
	delete mSelectionStrategy;
	setSelectionStrategy(nullptr);
	delete mCrossoverStrategy;
	setCrossoverStrategy(nullptr);
	delete mMutationStrategy;
	setMutationStrategy(nullptr);
}

void GAParameters::setToDefault()
{
	setPopulationSize(50);
	setEllitismSize(3);
	setConcurrentPopulationCount(1);
	setMaximumGenerationCount(150);

	delete mSolutionSample;
	setSolutionSample(nullptr);
	delete mSelectionStrategy;
	setSelectionStrategy(new SelectionRouletteWheel());
	delete mCrossoverStrategy;
	setCrossoverStrategy(new CrossoverSinglePointByChromosome());
	delete mMutationStrategy;
	setMutationStrategy(new MutationByChromosome());
}
