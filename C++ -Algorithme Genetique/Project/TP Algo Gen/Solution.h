#pragma once

#ifndef SOLUTION_H
#define SOLUTION_H

#include "Fitness.h"
#include "Chromosome.h"


class Solution
{
public:
	Solution();
	Solution(Solution const &) = default;
	Solution(Solution &&) = default;
	Solution& operator=(Solution const &) = delete;
	Solution& operator=(Solution &&) = delete;
	virtual ~Solution() = default;

	Chromosome const & chromosome() const;
	Chromosome & chromosome();
	fitness_t fitness() const;
	int nbTotalBits() const;

	virtual void processFitness() = 0;
	virtual void randomize() = 0;
	virtual void encode() = 0;
	virtual void decode() = 0;

	virtual void copy(Solution const & from);
	virtual Solution * clone() const = 0;

protected:
	Chromosome mChromosome;
	fitness_t mFitness;
	int nbTotalBitsAEncoder;

};

#endif // SOLUTION_H