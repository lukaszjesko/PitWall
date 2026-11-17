#include "lap_time.h"

#include <cmath>
#include <iomanip>
#include <sstream>

LapTime::LapTime() : ms_(0) {}

LapTime::LapTime(int milliseconds) : ms_(milliseconds) {}

LapTime LapTime::fromSeconds(double seconds) {
    return LapTime(static_cast<int>(std::lround(seconds * 1000.0)));
}

int LapTime::getMs() const {
    return ms_;
}

double LapTime::getSeconds() const {
    return ms_ / 1000.0;
}

// Format jak w F1: minuty:sekundy.milisekundy, np. 1:31.452
std::string LapTime::toString() const {
    int minutes = ms_ / 60000;
    int seconds = (ms_ / 1000) % 60;
    int millis = ms_ % 1000;
    std::ostringstream out;
    out << minutes << ':' << std::setw(2) << std::setfill('0') << seconds
        << '.' << std::setw(3) << std::setfill('0') << millis;
    return out.str();
}

// Odstęp do lidera w sekundach, np. +1.204
std::string LapTime::toGapString() const {
    std::ostringstream out;
    out << '+' << ms_ / 1000 << '.' << std::setw(3) << std::setfill('0')
        << ms_ % 1000;
    return out.str();
}

LapTime LapTime::operator+(const LapTime& other) const {
    return LapTime(ms_ + other.ms_);
}

LapTime LapTime::operator-(const LapTime& other) const {
    return LapTime(ms_ - other.ms_);
}

LapTime& LapTime::operator+=(const LapTime& other) {
    ms_ += other.ms_;
    return *this;
}

bool LapTime::operator<(const LapTime& other) const {
    return ms_ < other.ms_;
}

std::ostream& operator<<(std::ostream& out, const LapTime& time) {
    out << time.toString();
    return out;
}
