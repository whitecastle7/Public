
#include <algorithm>
#include "Population.h"


Population::~Population() {
	for (auto & s : mSolution) {
		delete s;
	}
}

size_t Population::size() const {
	return mSolution.size();
}

void Population::set(size_t size, Solution const & SolutionSample) {

	for (auto & s : mSolution) {
		delete s;
	}

	mSolution.resize(size);

	for (auto & s : mSolution) {
		s = SolutionSample.clone();
	}
}

Solution & Population::operator[](size_t pos) {
	return *mSolution.at(pos);
}

Solution const & Population::operator[](size_t pos) const {
	return *mSolution.at(pos);
}

void Population::processFitness() {
	for (Solution * sol : mSolution) {
		sol->processFitness();
	}
}

void Population::randomize() {
	for (Solution * sol : mSolution) {
		sol->randomize();
	}
}

void Population::encode() {
	for (Solution * sol : mSolution) {
		sol->encode();
	}
}

void Population::decode() {
	for (Solution * sol : mSolution) {
		sol->decode();
	}
}

void Population::sort() {
	std::sort(mSolution.begin(), mSolution.end(), [](Solution* a, Solution* b)
	{return a->fitness() < b->fitness();}	);
}

void Population::swap(Population & other) {
	mSolution.swap(other.mSolution);
}
