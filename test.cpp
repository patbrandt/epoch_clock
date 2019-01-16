#include <iomanip>
#include <iostream>

#include "clock.h"

// A clock that provides the current Julian day
// Julian time is in units of days, and has an epoch
// of noon on 1 January, 4713 BCE
using JulianClock = EpochClock<
    std::chrono::duration<long double, std::ratio<86400> > >;
template <>
const typename JulianClock::duration JulianClock::epoch{2440587.5};

// A clock that provides the current Gregorian time
// Gregorian time in units of 100ns. The Gregorian calendar
// has an epoch of midnight on 15 October, 1582 CE
using GregorianClock = EpochClock<
    std::chrono::duration<uint64_t, std::ratio<1, 10000000> > >;
template <>
const typename GregorianClock::duration GregorianClock::epoch{0x1b21dd213814000};

int main() {
    auto current_julian_time = JulianClock::now();
    std::cout << "Current Julian time = " << std::fixed
              << current_julian_time.time_since_epoch().count() << std::endl;

    auto current_greg_time = GregorianClock::now();
    std::cout << "Current Gregorian time = "
              << current_greg_time.time_since_epoch().count() << std::endl;

    GregorianClock::time_point time{GregorianClock::duration(137000856413280000ULL)};
    std::cout << "Converting " << time.time_since_epoch().count() << " to system time = "
              << GregorianClock::to_time_t(time) << std::endl;

    return 0;
}
