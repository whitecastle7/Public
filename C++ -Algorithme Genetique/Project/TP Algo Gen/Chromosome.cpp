
#include "Chromosome.h"


size_t Chromosome::size() const
{
	return mData.size();
}

void Chromosome::resize(size_t size)
{
	mData.resize(size);
}

std::vector<bool>::reference Chromosome::operator[](size_t pos)
{
	return mData[pos];
}

bool Chromosome::operator[](size_t pos) const
{
	return mData[pos];
}

void Chromosome::read(size_t & value, size_t from, size_t length) const
{
	value = 0;
	size_t masque = 1;

	for (size_t i{ from }; i < (from + length); ++i)
	{
		value += mData[i] ? masque : 0;
		masque <<= 1;
	}
}

void Chromosome::write(size_t value, size_t from, size_t length)
{
	size_t masque = 1;
	for (size_t i{ from }; i < (from + length); ++i)
	{
		mData[i] = value & masque ? 1 : 0;
		masque <<= 1;
	}
}

void Chromosome::flip(size_t pos)
{
	mData[pos] = !mData[pos];
}

void Chromosome::randomize(double probability)
{
	for (size_t i{}; i < mData.size(); ++i)
	{
		mData[i] = ((rand() % 2) < probability);
	}
}

void Chromosome::randomize(size_t from, size_t length, double probability)
{
	for (size_t i{ from }; i < (from + length); ++i)
	{
		mData[i] = ((rand() % 2) < probability);
	}
}
