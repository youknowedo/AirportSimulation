#include <deque>
#include <fstream>
#include <iostream>

#include "Aircraft.h"
#include "Master.h"
#include "Runway.h"
#include "Statistics.h"

int main() {
	srand(time(nullptr));

	auto master = Master();

	int numberOfIntervals;
	std::cin >> numberOfIntervals;

	master.nextIntervals(numberOfIntervals);

	auto stats = master.stats();
	std::cout << "Average wait: " << stats.averageAircraftWaitTime() << "\n";
	std::cout << "Longest wait: " << stats.longestAircraftWaitTime() << "\n";
	std::cout << "Runway busy: " << stats.numberOfTimeUnitsRunwayBusy() / static_cast<double>(numberOfIntervals) * 100
		<< "%\n";
}
