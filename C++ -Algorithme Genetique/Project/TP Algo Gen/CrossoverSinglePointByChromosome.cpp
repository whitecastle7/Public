
#include "CrossoverSinglePointByChromosome.h"


void CrossoverSinglePointByChromosome::breed(Solution const & genitor1, Solution const & genitor2, Solution & offspring)
{
	size_t size{ offspring.chromosome().size() };

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<size_t> unif(0, size - 1);
	//std::default_random_engine re;
	size_t pivot = unif(mt);

	for (size_t i{ 0 }; i < pivot; ++i)
	{
		offspring.chromosome()[i] = genitor1.chromosome()[i];
	}

	for (size_t j{ pivot }; j < size; ++j)
	{
		offspring.chromosome()[j] = genitor2.chromosome()[j];
	}
}
