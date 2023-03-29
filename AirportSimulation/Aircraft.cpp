#include "Aircraft.h"

#include <random>

Aircraft::Aircraft(
	const bool startsInAir,
	const int createTime,
	Runway *runway) : _startsInAir(startsInAir),
					  _createTime(createTime),
					  _fuel(startsInAir ? rand() % 20 : -1)
{
	if (startsInAir)
		runway->arrivingQueue().push_back(this);
	else
		runway->departingQueue().push_back(this);
}
