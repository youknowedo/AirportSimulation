#include "Statistics.h"

#include <iostream>

Statistics::Statistics() : _aircraftWaitTimes({}), _longestAircraftWaitTime(-1) {}

void Statistics::addAircraftStats(const int createTime, const int currentTime)
{
	const int waitTime = currentTime - createTime;

	_aircraftWaitTimes.push_back(waitTime);

	if (waitTime > _longestAircraftWaitTime)
		_longestAircraftWaitTime = waitTime;
}

double Statistics::averageAircraftWaitTime() const
{
	int timesAdded = 0;

	for (const int aircraftWaitTime : _aircraftWaitTimes)
	{
		timesAdded += aircraftWaitTime;
	}

	return static_cast<double>(timesAdded) / static_cast<double>(_aircraftWaitTimes.size());
}