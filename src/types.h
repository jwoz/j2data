//
// Created by j on 2020-06-06.
//

#ifndef J2DATA_TYPES_H
#define J2DATA_TYPES_H

#include <vector>
#include <map>

class tm_compare {
public:
    constexpr bool operator()(const tm &lhs, const tm &rhs) const {
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

typedef std::vector<double> vec_dbl_t;
typedef std::vector<std::vector<double> > vec_vec_dbl_t;
typedef std::vector<std::string> vec_string_t;
typedef std::map<tm, int, tm_compare> map_time_t;

#endif //J2DATA_TYPES_H
