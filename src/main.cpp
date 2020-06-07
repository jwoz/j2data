//
// Created by j on 2020-06-05.
//
#include <iostream>
#include <ctime>
#include "time_series.h"
#include <memory>
#include "tools.hpp"

using namespace std;

int main() {
    // ctime gymnastics
    time_t now = time(0);
    cout << "Number of sec since January 1,1970:" << now << endl;
    tm *ltm = localtime(&now);
    cout << "Year:" << 1900 + ltm->tm_year << endl;
    cout << "Month: " << 1 + ltm->tm_mon << endl;
    cout << "Day: " << ltm->tm_mday << endl;
    cout << "Time: " << 1 + ltm->tm_hour << ":";
    cout << 1 + ltm->tm_min << ":";
    cout << 1 + ltm->tm_sec << endl;
    // convert now to string form
    char *dt = ctime(&now);

    cout << "The local date and time is: " << dt << endl;

    // read time series
    auto ts_daily = make_shared<TimeSeries>("data/timeseries_1d.csv");
    auto ts_60min = make_shared<TimeSeries>("data/timeseries_60m.csv", "60m");
    std::cout << ts_daily->symbol() << ": " << ts_daily->count() << " daily quotes" << std::endl;
    std::cout << ts_daily->asc_minimum_time() << std::endl;
    std::cout << ts_daily->asc_maximum_time() << std::endl;

    ts_daily->range(create_tm(2020,1,1), create_tm(2020,3,1));


    return 0;
};

// TODO
// compute a moving average
// interpolate missing values
// compute standard deviation/ volatility
// GARCH/ ARIMA
// portfolio optimization
// integer programming

// ==>> which libraries to use???