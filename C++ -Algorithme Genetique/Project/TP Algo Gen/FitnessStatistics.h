#pragma once

#ifndef FITNESS_STATISTICS_H
#define FITNESS_STATISTICS_H

#include "Fitness.h"


struct FitnessStatistics
{
public:
	void reset();

	size_t count{ 0 };
	fitness_t minimum{ 0 };
	fitness_t maximum{ 0 };
	fitness_t average{ 0 };

};

#endif