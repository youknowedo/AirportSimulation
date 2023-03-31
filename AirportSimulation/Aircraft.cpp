#include "Aircraft.h"

#include <random>

Aircraft::Aircraft(
	const bool startsInAir,
	const int createTime,
	Runway *runway) : _startsInAir(startsInAir),
					  _createTime(createTime),
					  _fuel(startsInAir ? rand() % 15 + 5 : -1)
{
	if (startsInAir)
	{
		int i = 0;
		for (auto item = runway->arrivingQueue()->begin(); item != nullptr && (item->data()->fuel() < _fuel); ++item, ++i)
		{
			if (item->next() == nullptr)
				break;
		}

		runway->arrivingQueue()->push(this, i);
	}
	else
		runway->departingQueue()->pushBack(this);
}
