#include <list>
#include <fstream>
#include <iostream>

#include "Aircraft.h"
#include "Master.h"
#include "Runway.h"
#include "Statistics.h"

int main(int argc, char *argv[])
{
	srand(time(nullptr));

	auto master = Master();

	std::cout << "How many intervals do you want to simulate?\n>> ";
	int numberOfIntervals;
	std::cin >> numberOfIntervals;

	auto intervals = master.nextIntervals(numberOfIntervals);
	std::ofstream statFile;
	statFile.open("example.csv");
	for (int i = 0; i < intervals.size(); i++)
	{
		statFile << i << "," << intervals[i].queueSize() << "," << intervals[i].newPlane() << "," << intervals[i].message() << "\n";
	}
	statFile.close();

	auto stats = master.stats();
	std::cout << "Time elapsed: " << stats.timeElapsedInSeconds() << "\n";
	std::cout << "Average wait: " << stats.averageAircraftWaitTime() << "\n";
	std::cout << "Runway busy: " << stats.numberOfTimeUnitsRunwayBusy() / static_cast<double>(numberOfIntervals) * 100
			  << "%\n";
	std::cout << "Planes crashed: " << stats.numberOfAircraftCrashed() << "\n";
	std::cout << "Success rate: " << (100 - ((double)stats.numberOfAircraftCrashed() / (double)numberOfIntervals) * 100) << "%\n";
}
