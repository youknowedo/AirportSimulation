#pragma once

#include <fstream>
#include <iostream>

#include "Runway.h"
#include "Statistics.h"

/// @brief Holds data about an interval
class Interval
{
public:
	/// @brief Creates a new instance of the Interval class
	/// @param newPlane Wether or not it spawned a new aircraft that interval, and if that aircraft
	/// 				spawned in the air or on the ground. [-1: No aircraft, 0: Spawned on ground,
	///					1: Spawned in the air]
	/// @param queueSize The total size of the queues that interval
	/// @param message Any other additional notes
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

/**
 * Pulled this part of the
 */
/// @brief The master class of the simulation. Holds the runway, the statistics, and the number
/// 	   of intervals that had been simulated. Also holds the functions that simulate either
///		   one or multiple intervals.
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

// Binds this projects classes to JavaScript classes when building to WebAssembly
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
