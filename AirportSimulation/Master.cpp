#include "Master.h"
#include <random>
#include <chrono>

#include "Aircraft.h"

/// @brief Creates a new instance of the Master class
Master::Master() : _runway(new Runway), _stats(new Statistics), _interval(0)
{
    // Sets the seed fpr the random function based on the current time
    srand(time(nullptr));
}

/// @brief Simulates one interval
/// @return Data about the interval
Interval Master::nextInterval()
{
    // Add to the intervals-simulated counter
    ++_interval;

    // Initializes a message string so that we can append messages about the interval later on
    std::string message = "";

    /**
     * Initializes a variable for wether or not a new aircraft will be spawned.
     * If newPlane is -1, no plane will be spawned this interval
     * If newPlane is 0, a plane will be spawned on land
     * If newPlane is 1, a plane will be spawned in the air
     *
     * We then generate a random number between 0 and 10. If the number is more
     * than 1, we do nothing with it and newPlane stays at -1. This means that
     * there is a 20% chance that a plane will spawn (10% chance that it will
     * spawn on land, 10% chance that it will spawn in the air).
     * If the number less or equal to 1 a new plane will be spawned.
     */
    int newPlane = -1;
    const int r{rand() % 10};
    if (r <= 1)
    {
        message += "New Plane. ";
        newPlane = r;

        /**
         * Since if the aircraft should spawn on land, newPlane would be 0, and if
         * the aircraft should spawn in the air, newPlane would be 1, we can
         * convert newPlane into a bool and place it as startsInAir.
         */
        new Aircraft(newPlane, _interval, _runway);
    }

    /**
     * If the arriving queue isn't empty, decrease the fuel level of all planes in the
     * the queue by one.
     */
    if (!_runway->arrivingQueue()->empty())
    {
        // Keeping track of the item and index in the queue while iterating over them
        int i = 0;
        auto item = _runway->arrivingQueue()->front();

        /**
         * Iterating over every item in the queue.
         * Using a do-while loop since we know that this needs to run at least once (checked
         * if the queue was empty earlier). Also checking if the it has a next item in the
         * while expression. If i instead switch to a for- or while-loop it wouldn't run if
         * there was only one item in the queue. Could do it as a for- or while-loop and check
         * if it was the first iteration but I think that this is clearer.
         */
        do
        {
            // Decrease the fuel
            int newFuel = (item)->data()->decreaseFuel();

            // If there is no fuel left, remove the item from the queue
            if (newFuel <= 0)
            {
                // Delete the aircraft data inside of the item
                delete item->data();

                /**
                 * Go back one item since this one is going to be removed. We move to the item
                 * after the current one after it's been removed
                 */
                --i;
                item = item->prev();

                // Remove the item from the queue
                _runway->arrivingQueue()->pop(i);

                // Increment the crashed aircraft variable in stats
                _stats->addCrashedAircraft();
            }

            ++i;
        } while (item != nullptr && item->next() != nullptr && ++item);
    }

    // Check if the runway is busy (busyTil isn't -1)
    if (_runway->busyTil() != -1)
    {
        // Check if the runway should still be busy. If not, free the runway.
        if (_runway->busyTil() <= _interval)
        {
            // Free the runway
            _runway->busyTil(-1);
            message = "Runway free. ";

            /**
             * Since the arriving queue must be empty to start with the departing queue (all
             * departing planes have full fuel, meaning they have lower priority), we check
             * if the arriving queue isn't empty. If that is the case, we remove the first item
             * in the queue. If it isn't, we remove the first item in the departing queue.
             *
             * TODO: If a new aircraft spawns in the air while one is departing, the arriving
             * aircraft will land instead of the departing aircraft taking off. Fix this.
             */
            if (!_runway->arrivingQueue()->empty())
            {
                delete _runway->arrivingQueue()->front()->data();
                _runway->arrivingQueue()->popFront();
            }
            else if (!_runway->departingQueue()->empty())
            {
                delete _runway->departingQueue()->front()->data();
                _runway->departingQueue()->popFront();
            }
        }
    }
    // If the runway isn't busy and the arriving queue isn't empty, start landing a plane.
    else if (!_runway->arrivingQueue()->empty())
    {
        // Set the runway to busy
        _runway->busyTil(_interval + 3);

        _stats->addWaitTimeStats(_runway->arrivingQueue()->front()->data()->createTime(), _interval);
    }
    /**
     * If the runway isn't busy, the arriving queue is empty and the departing queue isn't
     * empty, start a takeoff.
     */
    else if (!_runway->departingQueue()->empty())
    {
        // Set the runway to busy
        _runway->busyTil(_interval + 3);

        _stats->addWaitTimeStats(_runway->departingQueue()->front()->data()->createTime(), _interval);
    }

    // Check if the runway is busy
    if (_runway->busyTil() != -1)
        _stats->addToNumberOfTimeUnitsRunwayBusy();

    // Return the interval data
    return Interval(newPlane, _runway->arrivingQueue()->size() + _runway->departingQueue()->size(), message);
}

/// @brief Simulates multiple intervals. Also records the time it takes and adds it to the statistics
/// @param intervals The amount of intervals that should be simulated
/// @return A vector with data about the intervals
std::vector<Interval> Master::nextIntervals(int intervals)
{
    std::vector<Interval> simulatedIntervals{};

    auto startTime = std::chrono::system_clock::now();

    for (int i = 0; i < intervals; i++)
    {
        simulatedIntervals.push_back(nextInterval());
    }

    auto endTime = std::chrono::system_clock::now();

    // Calculates how long the simulation took and adds it to the statistics
    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    _stats->addTimeElapsed(elapsedSeconds.count());

    return simulatedIntervals;
}
