//
// Created by j on 2020-06-05.
//

#ifndef J2DATA_TIME_SERIES_H
#define J2DATA_TIME_SERIES_H

#include <vector>
#include <string>
#include <ctime>
#include <memory>
#include <map>
#include "types.h"


class TimeSeries
{
    std::string m_symbol;
    map_time_t m_times;
    std::vector<std::string> m_columns;
    vec_vec_dbl_t m_data;
public:
    TimeSeries(map_time_t times, vec_string_t columns, vec_vec_dbl_t data);

    explicit TimeSeries(const std::string &filename, const std::string &period = "1d");

    virtual ~TimeSeries() = default;

    std::unique_ptr<TimeSeries> range(const tm &t0, const tm &t1) const;


    long count() const;

    std::string symbol() const;

    tm minimum_time() const;

    tm maximum_time() const;

    std::string asc_minimum_time() const;

    std::string asc_maximum_time() const;

    void print() const;

    const vec_dbl_t * get(const std::string &name) const;

    void add(const std::string &name, const vec_dbl_t &data);

};


#endif //J2DATA_TIME_SERIES_H
