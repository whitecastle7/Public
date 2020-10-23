#pragma once

#ifndef EVOLUTION_ENGINE_H
#define EVOLUTION_ENGINE_H

#include "PopulationEngine.h"
#include "FitnessStatisticsOverTime.h"
#include "GAParameters.h"
#include "Population.h"


class EvolutionEngine
{
public:
	EvolutionEngine() = default;
	~EvolutionEngine() = default;

	size_t currentGeneration() const;
	Population const & population() const;
	FitnessStatisticsOverTime const & fitnessStatistics() const;
	void setup(GAParameters & parameters);
	void evolveOneGeneration(GAParameters & parameters);

private:
	size_t mCurrentGeneration{};
	PopulationEngine mPopulationEngine;
	FitnessStatisticsOverTime mFitnessStatisticsOverEpoch;

};

#endif