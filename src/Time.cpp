#include "time.h"
#include <sstream>
#include <iomanip>

Time::Time(int h, int m) {
    Setter(h, m);
}

void Time::Setter(int h, int m) {
    if (m > MAX_MINUTE) {
        h += m / 60;
        m = m % 60;
    }
    if (h > MAX_HOUR) {
        h = h % 24;
    }
    hour = h;
    minute = m;
}

Time& Time::operator++() {
    ++minute;
    if (minute > MAX_MINUTE) {
        minute = 0;
        ++hour;
        if (hour > MAX_HOUR)
            hour = 0;
    }
    return *this;
}

std::string Time::GetTime() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hour
        << ":"
        << std::setw(2) << std::setfill('0') << minute;
    return oss.str();
}