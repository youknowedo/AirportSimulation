#include "Statistics.h"

#include <iostream>

Statistics::Statistics() : _aircraftWaitTimes({}) {}

void Statistics::addAircraftStats(const int createTime, const int currentTime)
{
	const int waitTime = currentTime - createTime;

	_aircraftWaitTimes.push_back(waitTime);
}

double Statistics::averageAircraftWaitTime() const
{
	int timesAdded = 0;

	for (const int waitTime : _aircraftWaitTimes)
	{
		timesAdded += waitTime;
	}

	return static_cast<double>(timesAdded) / static_cast<double>(_aircraftWaitTimes.size());
}