#pragma once
#include <list>
#include "Queue.h"

/**
 * Forward-declaring the Aircraft class because both Aircraft and Runway depend on each other.
 * Prevents circular class dependency
 */
class Aircraft;

/// @brief The runway. Holds the queues
class Runway
{
public:
	/// @brief Creates a new instance of the Runway class
	Runway() : _arrivingQueue(new Queue<Aircraft *>()),
			   _departingQueue(new Queue<Aircraft *>()),
			   _busyTil(-1) {}

	Queue<Aircraft *> *arrivingQueue() { return _arrivingQueue; }
	Queue<Aircraft *> *departingQueue() { return _departingQueue; }

	const int busyTil() const { return _busyTil; }
	const int busyTil(const int til) { return _busyTil = til; }

private:
	Queue<Aircraft *> *_arrivingQueue;
	Queue<Aircraft *> *_departingQueue;
	int _busyTil;
};
