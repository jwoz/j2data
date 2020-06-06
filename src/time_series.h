//
// Created by j on 2020-06-05.
//

#ifndef J2DATA_TIME_SERIES_H
#define J2DATA_TIME_SERIES_H

#include <vector>
#include <string>
#include <ctime>
#include <map>

class tm_compare {
public:
    constexpr bool operator()(const std::tm &lhs, const std::tm &rhs) const {
        if (lhs.tm_year < rhs.tm_year) return true;
        if (lhs.tm_year > rhs.tm_year) return false;
        if (lhs.tm_mon < rhs.tm_mon) return true;
        if (lhs.tm_mon > rhs.tm_mon) return false;
        if (lhs.tm_mday < rhs.tm_mday) return true;
        if (lhs.tm_mday > rhs.tm_mday) return false;
        if (lhs.tm_hour < rhs.tm_hour) return true;
        if (lhs.tm_hour > rhs.tm_hour) return false;
        if (lhs.tm_min < rhs.tm_min) return true;
        if (lhs.tm_min > rhs.tm_min) return false;
        // TODO time zones and seconds etc or
        return false;
    };
};


class TimeSeries {
    std::string m_symbol;
    std::map<tm, int, tm_compare> m_times;
    std::vector<double> m_open;
    std::vector<double> m_close;
    std::vector<double> m_high;
    std::vector<double> m_low;
public:
    explicit TimeSeries(const std::string &filename, const std::string &period = "1d");

    virtual ~TimeSeries() = default;

    long count() const;
    std::string symbol() const;

};


#endif //J2DATA_TIME_SERIES_H
