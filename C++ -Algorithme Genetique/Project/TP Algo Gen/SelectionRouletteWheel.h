#pragma once

#ifndef SELECTION_ROULETTE_WHEEL_H
#define SELECTION_ROULETTE_WHEEL_H

#include <vector>
#include <random>

#include "SelectionStrategy.h"
#include "Population.h"
#include "Solution.h"
#include "FitnessStatistics.h"


class SelectionRouletteWheel : public SelectionStrategy
{
public:
	SelectionRouletteWheel() = default;
	~SelectionRouletteWheel() = default;

	void prepare(Population const & population) override;
	Solution const & select(Population const & population) override;

protected:
	std::vector<double> mRankWeight;

private:
	bool mIsFitnessValid{ true };

};

#endif // SELECTION_ROULETTE_WHEEL_H