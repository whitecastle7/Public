#pragma once

#ifndef FITNESS_STATISTICS_OVER_TIME_H
#define FITNESS_STATISTICS_OVER_TIME_H

#include <vector>

#include "FitnessStatistics.h"


class FitnessStatisticsOverTime
{
public:
	FitnessStatisticsOverTime() = default;
	~FitnessStatisticsOverTime() = default;

	std::vector<FitnessStatistics> statisticsOverTime;

};

#endif