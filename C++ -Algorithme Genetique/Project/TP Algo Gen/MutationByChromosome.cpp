
#include "MutationByChromosome.h"


void MutationByChromosome::setMutationRate(double mutationRate)
{
	mMutationRate = mutationRate;
}

double MutationByChromosome::mutationRate()
{
	return mMutationRate;
}

void MutationByChromosome::mutate(Solution & offspring)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> unif(0.0, 1.0);
	//std::default_random_engine re;
	bool doMutate = unif(mt) < mMutationRate;

	if (doMutate)
	{
		std::random_device rd;
		std::mt19937 nt(rd());
		std::uniform_int_distribution<size_t> unif(0, offspring.chromosome().size());
		//std::default_random_engine re;
		size_t bitToMutate = unif(nt);

		offspring.chromosome().flip(bitToMutate);
	}
}
