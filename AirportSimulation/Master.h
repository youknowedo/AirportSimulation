#pragma once

#include <fstream>
#include <iostream>

#include "Runway.h"
#include "Statistics.h"

class Interval
{
public:
	Interval(int newPlane, int queueSize, std::string message) : _newPlane(newPlane), _queueSize(queueSize),
																 _message(message) {}

	int newPlane() const { return _newPlane; }
	int queueSize() const { return _queueSize; }
	std::string message() const { return _message; }

private:
	int _newPlane;
	int _queueSize;
	std::string _message;
};

class Master
{
public:
	Master();

	Statistics stats() { return *_stats; }

	Interval nextInterval();
	std::vector<Interval> nextIntervals(int intervals);

private:
	Runway *_runway;
	Statistics *_stats;

	int _interval;
};

#ifdef __EMSCRIPTEN__
#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS(master)
{
	class_<Interval>("Interval")
		.constructor<int, int, std::string>()
		.property("newPlane", &Interval::newPlane)
		.property("queueSize", &Interval::queueSize)
		.property("message", &Interval::message);
	register_vector<Interval>("VectorInterval");

	class_<Statistics>("Statistics")
		.constructor<>()
		.property("averageAircraftWaitTime", &Statistics::averageAircraftWaitTime)
		.property("numberOfTimeUnitsRunwayBusy", &Statistics::numberOfTimeUnitsRunwayBusy)
		.property("timeElapsedInSeconds", &Statistics::timeElapsedInSeconds);

	class_<Master>("Master")
		.constructor<>()
		.function("stats", &Master::stats)
		.function("nextInterval", &Master::nextInterval)
		.function("nextIntervals", &Master::nextIntervals);
}
#endif
