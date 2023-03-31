#include "Master.h"
#include <random>
#include <chrono>

#include "Aircraft.h"

Master::Master() : _runway(new Runway), _stats(new Statistics), _interval(0)
{
    srand(time(nullptr));
}

Interval Master::nextInterval()
{
    ++_interval;

    int newPlane = -1;
    std::string message = "";
    const int r{rand() % 10};
    if (r <= 1)
    {
        message = "New Plane. ";
        new Aircraft(r, _interval, _runway);
        newPlane = r;
    }

    if (!_runway->arrivingQueue()->empty())
    {
        int i = 0;
        auto item = _runway->arrivingQueue()->begin();
        do
        {
            int newFuel = (item)->data()->decreaseFuel();

            if (newFuel <= 0)
            {
                item = item->prev();

                delete (*_runway->arrivingQueue())[i]->data();
                _runway->arrivingQueue()->pop(i);
                _stats->addCrashedAircraft();
            }

            ++i;
        } while (item != nullptr && item->next() != nullptr && ++item);
    }

    if (_runway->busyTil() != -1)
    {
        if (_runway->busyTil() <= _interval)
        {
            message = "Runway free. ";
            _runway->busyTil(-1);

            if (!_runway->arrivingQueue()->empty())
            {
                _runway->arrivingQueue()->popFront();
            }
            else if (!_runway->departingQueue()->empty())
            {
                _runway->departingQueue()->popFront();
            }
        }
    }
    else if (!_runway->arrivingQueue()->empty())
    {
        _runway->busyTil(_interval + 3);
        _stats->addAircraftStats(_runway->arrivingQueue()->begin()->data()->createTime(), _interval);
    }
    else if (!_runway->departingQueue()->empty())
    {
        _runway->busyTil(_interval + 3);
        _stats->addAircraftStats(_runway->departingQueue()->begin()->data()->createTime(), _interval);
    }

    if (_runway->busyTil() != -1)
        _stats->addToNumberOfTimeUnitsRunwayBusy();

    return Interval(newPlane, _runway->arrivingQueue()->size(), message);
}

std::vector<Interval> Master::nextIntervals(int intervals)
{
    std::vector<Interval> simulatedIntervals;

    auto startTime = std::chrono::system_clock::now();
    for (int i = 0; i < intervals; i++)
    {
        simulatedIntervals.push_back(this->nextInterval());
    }
    auto endTime = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsedSeconds = endTime - startTime;
    _stats->addTimeElapsed(elapsedSeconds.count());

    return simulatedIntervals;
}
