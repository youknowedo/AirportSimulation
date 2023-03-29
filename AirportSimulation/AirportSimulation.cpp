#include <deque>
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

	master.nextIntervals(numberOfIntervals);

	auto stats = master.stats();
	std::cout << "Time elapsed: " << stats.timeElapsedInSeconds() << "\n";
	std::cout << "Average wait: " << stats.averageAircraftWaitTime() << "\n";
	std::cout << "Runway busy: " << stats.numberOfTimeUnitsRunwayBusy() / static_cast<double>(numberOfIntervals) * 100
			  << "%\n";
}
