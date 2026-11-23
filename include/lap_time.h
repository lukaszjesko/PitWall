#ifndef PITWALL_LAP_TIME_H
#define PITWALL_LAP_TIME_H

#include <ostream>
#include <string>

// Czas w milisekundach: jedno okrążenie, postój albo cały wyścig.
class LapTime {
public:
    LapTime();
    
    explicit LapTime(int milliseconds);

    static LapTime fromSeconds(double seconds);

    int getMs() const;
    double getSeconds() const;
    std::string toString() const;
    std::string toGapString() const;

    LapTime operator+(const LapTime& other) const;
    LapTime operator-(const LapTime& other) const;
    LapTime& operator+=(const LapTime& other);
    bool operator<(const LapTime& other) const;

private:
    int ms_;
};

std::ostream& operator<<(std::ostream& out, const LapTime& time);

#endif
