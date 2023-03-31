#pragma once
#include <list>
#include "Queue.h"

class Aircraft;

class Runway
{
public:
	Runway();
	~Runway();

	Queue<Aircraft *> *arrivingQueue(Queue<Aircraft *> *newQueue) { return _arrivingQueue = newQueue; }
	Queue<Aircraft *> *arrivingQueue() { return _arrivingQueue; }
	Queue<Aircraft *> *departingQueue() { return _departingQueue; }
	const int busyTil() const { return _busyTil; }
	const int busyTil(const int til) { return _busyTil = til; }

private:
	Queue<Aircraft *> *_arrivingQueue;
	Queue<Aircraft *> *_departingQueue;
	int _busyTil;
};
