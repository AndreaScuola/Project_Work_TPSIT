#ifndef TIME_H
#define TIME_H

#include <string>

class Time {
private:
    int hour;
    int minute;

public:
    static const int MIN_HOUR   = 0;
    static const int MAX_HOUR   = 23;
    static const int MIN_MINUTE = 0;
    static const int MAX_MINUTE = 59;

    Time(int h = 0, int m = 0);

    void Setter(int h, int m);
    Time& operator++();
    std::string GetTime() const;
};

#endif // TIME_H bo scrivo a caso