#pragma once

#ifndef POPULATION_H
#define POPULATION_H

#include <Solution.h>
#include <vector>


class Population {

public:
	Population() = default;
	~Population();

	size_t size() const;
	void set(size_t size, Solution const & SolutionSample);

	Solution & operator[](size_t pos);
	Solution const & operator[](size_t pos) const;

	void processFitness();
	void randomize();
	void encode();
	void decode();
	void sort();
	void swap(Population & other);

private:
	std::vector<Solution*> mSolution;

};

#endif // POPULATION_H