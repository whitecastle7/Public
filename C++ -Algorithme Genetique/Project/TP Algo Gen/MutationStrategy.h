#pragma once

#ifndef MUTATION_STRATEGY_H
#define MUTATION_STRATEGY_H

#include "Solution.h"


class MutationStrategy
{
public:
	MutationStrategy() = default;
	~MutationStrategy() = default;

	virtual void setMutationRate(double mutationRate) = 0;
	virtual double mutationRate() = 0;
	virtual void mutate(Solution & offspring) = 0;

private:
	double mMutationRate;

};

#endif MUTATION_STRATEGY_H