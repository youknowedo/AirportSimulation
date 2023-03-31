#include "Aircraft.h"

#include <random>

/// @brief Creates a new instance of the Aircraft class
/// @param startsInAir Whether or not the aircraft is spawned in the air
/// @param createTime The interval number it was created
/// @param runway A pointer to the runway it is going to use
Aircraft::Aircraft(
	const bool startsInAir,
	const int createTime,
	Runway *runway) : _startsInAir(startsInAir),
					  _createTime(createTime),
					  /**
					   * If the aircraft spawns in the air, generate a number between 5 and 20
					   * and set it as the fuel level.
					   */
					  _fuel(startsInAir ? rand() % 15 + 5 : -1)
{
	if (startsInAir)
	{
		/**
		 * Puts new aircraft in the array so that it is sorted.
		 * Iterate through the entire arriving queue. Saves the index in 'i.'
		 * Stops when the fuel in the current iterated aircraft is more than the the fuel level
		 * in the newly instanced aircraft
		 */
		int i = 0;
		for (auto item = runway->arrivingQueue()->front();
			 item != nullptr && (item->data()->fuel() <= _fuel);
			 ++item, ++i)
		{
			// If its the last in the queue, break the loop
			if (item->next() == nullptr)
				break;
		}
		runway->arrivingQueue()->push(this, i);
	}
	else
		runway->departingQueue()->pushBack(this);
}
