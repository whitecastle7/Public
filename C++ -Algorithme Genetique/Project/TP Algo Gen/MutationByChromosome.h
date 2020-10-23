#pragma once

#ifndef MUTATION_BY_CHROMOSOME_H
#define MUTATION_BY_CHROMOSOME_H

#include <random>

#include "MutationStrategy.h"
#include "Solution.h"


class MutationByChromosome : public MutationStrategy
{
public:
	MutationByChromosome() = default;
	~MutationByChromosome() = default;

	void setMutationRate(double mutationRate);
	double mutationRate();
	virtual void mutate(Solution & offspring);

private:
	double mMutationRate;

};

#endif  // MUTATION_BY_CHROMOSOME_H