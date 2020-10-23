#pragma once

#ifndef CHROMOSOMES_H
#define CHROMOSOMES_H

#include <vector>


class Chromosome {
public:
	Chromosome() = default;
	~Chromosome() = default;

	size_t size() const;
	void resize(size_t size);
	std::vector<bool>::reference operator[](size_t pos);
	bool operator[](size_t pos) const;
	void read(size_t &value, size_t from, size_t length)const;
	void write(size_t value, size_t from, size_t length);
	void flip(size_t pos);
	void randomize(double probability = 0.5);
	void randomize(size_t from, size_t to, double probability = 0.5);

private:
	std::vector<bool> mData;

};

#endif // CHROMOSOMES_H