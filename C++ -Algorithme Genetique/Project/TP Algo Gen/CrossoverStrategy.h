#pragma once

#ifndef CROSSOVER_STRATEGY_H
#define CROSSOVER_STRATEGY_H

class Solution;


class CrossoverStrategy
{
public:
	CrossoverStrategy() = default;
	~CrossoverStrategy() = default;

	virtual void breed(Solution const & genitor1, Solution const & genitor2, Solution & offspring) = 0;

};

#endif //CROSSOVER_STRATEGY_H
