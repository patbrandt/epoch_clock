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

// A clock that provides the current CORBA time
// CORBA time is in units of 100ns, and has an epoch
// of midnight on 15 October, 1582 CE
using CorbaClock = EpochClock<
    std::chrono::duration<uint64_t, std::ratio<1, 10000000> > >;
template <>
const typename CorbaClock::duration CorbaClock::epoch{0x1b21dd213814000};

int main() {
    auto current_julian_time = JulianClock::now();
    std::cout << "Current Julian time = " << std::fixed
              << current_julian_time.time_since_epoch().count() << std::endl;

    auto current_corba_time = CorbaClock::now();
    std::cout << "Current CORBA time = "
              << current_corba_time.time_since_epoch().count() << std::endl;

    CorbaClock::time_point time{CorbaClock::duration(137000856413280000ULL)};
    std::cout << "Converting " << time.time_since_epoch().count() << " to system time = "
              << CorbaClock::to_time_t(time) << std::endl;

    return 0;
}
