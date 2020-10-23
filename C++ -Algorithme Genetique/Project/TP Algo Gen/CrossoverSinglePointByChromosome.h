#pragma once

#ifndef CROSSOVER_SINGLE_POINT_BY_CHROMOSOME_H
#define CROSSOVER_SINGLE_POINT_BY_CHROMOSOME_H

#include "CrossoverStrategy.h"
#include "Solution.h"
#include <random>


class CrossoverSinglePointByChromosome : public CrossoverStrategy
{
public:
	CrossoverSinglePointByChromosome() = default;
	~CrossoverSinglePointByChromosome() = default;

	void breed(Solution const & genitor1, Solution const & genitor2, Solution & out_offspring) override;

};

#endif //CROSSOVER_SINGLE_POINT_BY_CHROMOSOME_H
