#ifndef EPOCHCLOCK_H
#define EPOCHCLOCK_H

#include <chrono>

template <typename DURATION, typename REF_CLOCK = std::chrono::system_clock>
class EpochClock {
    using reference_clock = REF_CLOCK;

public:
    using rep = typename DURATION::rep;
    using period = typename DURATION::period;
    using duration = DURATION;
    using time_point = std::chrono::time_point<EpochClock, duration>;

    // NB: This must be manually initialized by a client to work correctly!
    // The epoch of a clock is the zero point. Here we define it as the delta
    // between the intended epoch and the epoch of the reference clock; this is
    // typically 00:00:00 UTC (midnight) on 1 January, 1970 for Unix system
    // clocks. Be sure to match the delta to the duration representation!
    static const duration epoch;

    static constexpr bool is_steady = reference_clock::is_steady;

    static time_point now() noexcept {
        time_point t{std::chrono::duration_cast<duration>(
            reference_clock::now().time_since_epoch())};
        return t + std::chrono::duration_cast<duration>(epoch);
    }

    // Convert from custom time to std::time_t
    static std::time_t to_time_t(const time_point &t) {
        // This will turn out badly if a time before the
        // system epoch is converted
        return std::time_t(
            (std::chrono::duration_cast<std::chrono::seconds>(
                t.time_since_epoch()) - epoch).count());
    }

    // Convert from std::time_t to custom time
    static time_point from_time_t(std::time_t t) {
        return std::chrono::time_point_cast<duration>(
            std::chrono::time_point<EpochClock, std::chrono::seconds>(
                std::chrono::seconds(t) + epoch));
    }
};

#endif//EPOCHCLOCK_H
