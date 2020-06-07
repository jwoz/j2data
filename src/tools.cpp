#include "tools.hpp"

tm create_tm(int year, int month, int day, int hour, int minute, int second) {
    std::tm t = {};
    t.tm_year = year;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = second;
    return t;
}
