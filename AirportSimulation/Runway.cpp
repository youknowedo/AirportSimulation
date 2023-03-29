#include "Runway.h"

Runway::Runway() : _arrivingQueue({}), _departingQueue({}), _busyTil(-1) {}
Runway::~Runway() = default;