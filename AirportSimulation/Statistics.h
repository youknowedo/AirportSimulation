#pragma once
#include <vector>

class Statistics
{
public:
	Statistics();

	void addAircraftStats(int createTime, int currentTime);

	double averageAircraftWaitTime() const;

	int longestAircraftWaitTime() const { return _longestAircraftWaitTime; }

	int numberOfTimeUnitsRunwayBusy() const { return _numberOfTimeUnitsRunwayBusy; }
	int addToNumberOfTimeUnitsRunwayBusy() { return ++_numberOfTimeUnitsRunwayBusy; }

private:
	std::vector<int> _aircraftWaitTimes;
	int _longestAircraftWaitTime;
	int _numberOfTimeUnitsRunwayBusy;
};
