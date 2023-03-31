#include "Statistics.h"

#include <iostream>

/// @brief Adds a wait time to the statistics
/// @param createTime The interval it was created
/// @param currentTime The current interval
void Statistics::addWaitTimeStats(const int createTime, const int currentTime)
{
	const int waitTime = currentTime - createTime;

	_aircraftWaitTimes.push_back(waitTime);
}

/// @brief Averages out the wait times
/// @return The average wait time for an aircraft
double Statistics::averageAircraftWaitTime() const
{
	int timesAdded = 0;

	for (const int waitTime : _aircraftWaitTimes)
	{
		timesAdded += waitTime;
	}

	return static_cast<double>(timesAdded) / static_cast<double>(_aircraftWaitTimes.size());
}