#pragma once

#ifndef POPULATION_ENGINE_H
#define POPULATION_ENGINE_H

#include "Population.h"
#include "FitnessStatistics.h"
#include "GAParameters.h"


class PopulationEngine
{
public:
	PopulationEngine() = default;
	~PopulationEngine() = default;

	Population const & population() const;
	FitnessStatistics const & fitnessStatistics() const;
	void setup(GAParameters & parameters);
	void evolveOneGeneration(GAParameters & parameters);

private:
	void processElitisme(size_t elitismSize);
	void processOneOffspring(GAParameters & parameters, size_t position);
	void finalizeCurrentEvolution();
	void processStatistics();

	Population mPopulation;
	Population mNextPopulation;
	FitnessStatistics mFitnessStatistics;

};

#endif