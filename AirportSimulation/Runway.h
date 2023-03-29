#pragma once
#include <deque>

class Aircraft;

class Runway {
public:
	Runway();
	~Runway();

	std::deque<Aircraft*>& queue() { return _queue; }
	int busyTil() const { return _busyTil; }
	int busyTil(const int til) { return _busyTil = til; }

private:
	std::deque<Aircraft*> _queue;
	int _busyTil;
};
