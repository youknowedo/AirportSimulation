#pragma once
#include <vector>

class Statistics
{
public:
	Statistics();

	void addAircraftStats(int createTime, int currentTime);

	double averageAircraftWaitTime() const;

	int numberOfTimeUnitsRunwayBusy() const { return _numberOfTimeUnitsRunwayBusy; }
	int addToNumberOfTimeUnitsRunwayBusy() { return ++_numberOfTimeUnitsRunwayBusy; }

	int numberOfAircraftCrashed() const { return _numberOfAircraftCrashed; }
	int addCrashedAircraft() { return _numberOfAircraftCrashed++; }

	double timeElapsedInSeconds() const { return _timeElapsedInSeconds; }
	double addTimeElapsed(double timeInSeconds) { return _timeElapsedInSeconds += timeInSeconds; }

private:
	std::vector<int> _aircraftWaitTimes;
	int _numberOfTimeUnitsRunwayBusy;
	int _numberOfAircraftCrashed;
	double _timeElapsedInSeconds;
};
