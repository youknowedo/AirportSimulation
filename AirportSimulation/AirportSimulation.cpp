#include <list>
#include <fstream>
#include <iostream>
#include <format>
#include <string>

#include "Aircraft.h"
#include "Master.h"
#include "Runway.h"
#include "Statistics.h"

int main(int argc, char *argv[])
{
	// Instantiates a new master to handle everything.
	auto master = Master();

	// Gets the number of intervals it is supposed to simulate
	std::cout << "How many intervals do you want to simulate?\n>> ";
	int numberOfIntervals;
	std::cin >> numberOfIntervals;

	// Simulates the intervals
	auto intervals = master.nextIntervals(numberOfIntervals);

	// Print out all of the statistics
	auto stats = master.stats();
	std::cout << "Time elapsed: " << stats.timeElapsedInSeconds() << "\n";
	std::cout << "Average wait: " << stats.averageAircraftWaitTime() << "\n";
	std::cout << "Runway busy: " << stats.numberOfTimeUnitsRunwayBusy() / static_cast<double>(numberOfIntervals) * 100
			  << "%\n";
	std::cout << "Planes crashed: " << stats.numberOfAircraftCrashed() << "\n";
	std::cout << "Success rate: " << (100 - ((double)stats.numberOfAircraftCrashed() / (double)numberOfIntervals) * 100) << "%\n";

	/**
	 * Creates a csv file and takes the interval data, iterates over it
	 * and append it to the csv file.
	 */
	std::ofstream statFile;
	auto fileName = std::format("stats-{}.csv", rand());
	statFile.open(fileName);

	for (int i = 0; i < intervals.size(); i++)
	{
		statFile << i << "," << intervals[i].queueSize() << "," << intervals[i].newPlane() << "," << intervals[i].message() << "\n";
	}
	statFile.close();

	system(fileName.c_str());
}
