#include "Runway.h"

Runway::Runway() : _arrivingQueue(new Queue<Aircraft *>()), _departingQueue(new Queue<Aircraft *>()), _busyTil(-1) {}
Runway::~Runway() = default;