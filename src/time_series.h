//
// Created by j on 2020-06-05.
//

#ifndef J2DATA_TIME_SERIES_H
#define J2DATA_TIME_SERIES_H

#include <vector>
#include <string>
#include <ctime>

class TimeSeries {
    std::vector<tm> m_times;
    std::vector<double> m_open;
    std::vector<double> m_close;
    std::vector<double> m_high;
    std::vector<double> m_low;
public:
    explicit TimeSeries(const std::string &filename, const std::string & period = "1d");
    virtual ~TimeSeries() = default;


};


#endif //J2DATA_TIME_SERIES_H
