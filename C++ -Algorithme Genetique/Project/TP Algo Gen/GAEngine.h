#pragma once

#ifndef GA_ENGINE_H
#define GA_ENGINE_H

#include <vector>
#include <list>
#include <algorithm>

#include "GAParameters.h"
#include "EvolutionEngine.h"
#include "Population.h"
#include "FitnessStatisticsOverTime.h"


class GAEngine
{
public:
	GAEngine() = default;
	~GAEngine() = default;

	enum EvolutionStatus
	{
		NeverStarted = 0,
		InProcess = 1,
		SolutionAvailable = 2
	};

	class EvolutionObserver
	{
	public:
		EvolutionObserver() = default;
		~EvolutionObserver() = default;

		virtual void update(GAEngine const & engine) = 0;
	};

	size_t currentGeneration() const;
	Population const & population(size_t populationIndex = 0) const;
	FitnessStatisticsOverTime const & fitnessStatistics(size_t populationIndex = 0) const;
	void evolveUntilConvergence(GAParameters & parameters);
	void stopEvolution();
	void registerObserver(EvolutionObserver & observer);
	void unregisterObserver(EvolutionObserver & observer);
	void unregisterObserver();
	void updateObservers();

private:
	GAEngine::EvolutionStatus mEvolutionStatus{ NeverStarted };
	std::vector<EvolutionEngine> mEvolutionEngine;
	std::list<EvolutionObserver*> mObservers;

};

#endif // GA_ENGINE_H