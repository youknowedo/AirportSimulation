#include "Runway.h"

Runway::Runway() : _queue({}), _busyTil(-1) {}
Runway::~Runway() = default;