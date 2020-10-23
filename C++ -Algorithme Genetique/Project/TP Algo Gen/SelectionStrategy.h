#pragma once

#ifndef SELECTION_STRATEGY_H
#define SELECTION_STRATEGY_H

class Population;
class Solution;


class SelectionStrategy
{
public:
	SelectionStrategy() = default;
	~SelectionStrategy() = default;

	virtual void prepare(Population const & population) = 0;
	virtual Solution const & select(Population const & population) = 0;

private:


};

#endif //SELECTION_STRATEGY_H