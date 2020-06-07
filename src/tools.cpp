#include "tools.h"

tm create_tm(int year, int month, int day, int hour, int minute, int second)
{
    std::tm t = {};
    t.tm_year = year;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    t.tm_hour = hour;
    t.tm_min = minute;
    t.tm_sec = second;
    return t;
}

std::string zero_padded(int v)
{
    if (v > 9) return std::to_string(v);
    return "0" + std::to_string(v);
};

std::string to_string_tm(const tm &t)
{
    return std::to_string(t.tm_year) + zero_padded(t.tm_mon + 1) + zero_padded(t.tm_mday) + "T" + zero_padded(t.tm_hour) + zero_padded(t.tm_min);
}
