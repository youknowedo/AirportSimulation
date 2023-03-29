#include "Master.h"
#include <random>

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
        message = "New Plane";
        _runway->queue().push_back(new Aircraft(r, _interval));
        newPlane = r;
    }

    if (_runway->busyTil() != -1)
    {
        if (_runway->busyTil() <= _interval)
        {
            message = "Runway free";
            _runway->busyTil(-1);

            delete _runway->queue().front();
            _runway->queue().pop_front();
        }
    }
    else if (!_runway->queue().empty())
    {
        _runway->busyTil(_interval + 3);
        _stats->addAircraftStats(_runway->queue().front()->createTime(), _interval);
    }

    if (_runway->busyTil() != -1)
        _stats->addToNumberOfTimeUnitsRunwayBusy();

    return Interval(newPlane, _runway->queue().size(), message);
}

std::vector<Interval> Master::nextIntervals(int intervals)
{
    std::vector<Interval> simulatedIntervals;

    for (int i = 0; i < intervals; i++)
    {
        simulatedIntervals.push_back(this->nextInterval());
    }

    return simulatedIntervals;
}
