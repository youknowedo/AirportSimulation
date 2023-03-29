#pragma once
#include <deque>

class Aircraft;

class Runway
{
public:
	Runway();
	~Runway();

	std::deque<Aircraft *> &arrivingQueue(std::deque<Aircraft *> newQueue) { return _arrivingQueue = newQueue; }
	std::deque<Aircraft *> &arrivingQueue() { return _arrivingQueue; }
	std::deque<Aircraft *> &departingQueue() { return _departingQueue; }
	const int busyTil() const { return _busyTil; }
	const int busyTil(const int til) { return _busyTil = til; }

private:
	std::deque<Aircraft *> _arrivingQueue;
	std::deque<Aircraft *> _departingQueue;
	int _busyTil;
};
