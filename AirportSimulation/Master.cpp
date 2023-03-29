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

    for (size_t i = 0; i < _runway->arrivingQueue().size(); i++)
    {
        auto aircraft = _runway->arrivingQueue()[i];

        int newFuel = aircraft->decreaseFuel();
        if (newFuel <= 0)
        {
            std::deque<Aircraft *> newQueue;

            for (size_t j = 0; j < _runway->arrivingQueue().size(); j++)
            {
                auto a = _runway->arrivingQueue()[j];

                if (j != i)
                    newQueue.push_back(a);
            }

            // TODO: Make work. Throws error "Segmentation fault (core dumped)"
            // _runway->arrivingQueue(newQueue);
        }
    }

    if (_runway->busyTil() != -1)
    {
        if (_runway->busyTil() <= _interval)
        {
            message = "Runway free. ";
            _runway->busyTil(-1);

            if (!_runway->arrivingQueue().empty())
            {
                delete _runway->arrivingQueue().front();
                _runway->arrivingQueue().pop_front();
            }
            else
            {
                delete _runway->departingQueue().front();
                _runway->departingQueue().pop_front();
            }
        }
    }
    else if (!_runway->arrivingQueue().empty())
    {
        _runway->busyTil(_interval + 3);
        _stats->addAircraftStats(_runway->arrivingQueue().front()->createTime(), _interval);
    }
    else if (!_runway->departingQueue().empty())
    {
        _runway->busyTil(_interval + 3);
        _stats->addAircraftStats(_runway->departingQueue().front()->createTime(), _interval);
    }

    if (_runway->busyTil() != -1)
        _stats->addToNumberOfTimeUnitsRunwayBusy();

    return Interval(newPlane, _runway->arrivingQueue().size(), message);
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
