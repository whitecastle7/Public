
#include <Solution.h>
//#include "Solution.h"
#include <vector>
#include "Solution.h"


Solution::Solution()
	: mChromosome{}, mFitness{}
{
}

Chromosome const & Solution::chromosome() const {
	return mChromosome;
}

Chromosome & Solution::chromosome() {
	return mChromosome;
}

fitness_t Solution::fitness() const {
	return mFitness;
}

int Solution::nbTotalBits() const
{
	return nbTotalBitsAEncoder;
}

void Solution::copy(Solution const & from) {
	mChromosome = from.mChromosome;
	mFitness = from.mFitness;
}
