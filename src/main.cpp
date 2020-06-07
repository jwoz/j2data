//
// Created by j on 2020-06-05.
//
#include <iostream>
#include <ctime>
#include "time_series.h"
#include <memory>
#include "tools.h"
#include "operate.h"

using namespace std;

int main()
{
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

    // vector of strings
    vec_string_t strings = {"abc", "def"};
    cout << strings[0] << endl;
    auto idx = findElement<string>(strings, "def");
    cout << idx.first << " " << idx.second << endl;

    // read time series
    auto ts_daily = make_shared<TimeSeries>("data/timeseries_1d.csv");
    auto ts_60min = make_shared<TimeSeries>("data/timeseries_60m.csv", "60m");
    std::cout << ts_daily->symbol() << ": " << ts_daily->count() << " daily quotes" << std::endl;
    std::cout << ts_daily->asc_minimum_time() << std::endl;
    std::cout << ts_daily->asc_maximum_time() << std::endl;
    ts_daily->print();

    std::cout << "Extract sub range" << std::endl;
    auto ts_sub = ts_daily->range(create_tm(2020, 1, 1), create_tm(2020, 3, 1));
    ts_sub->print();

    std::cout << "Simple moving average" << std::endl;
    vec_dbl_t sma = simpleMovingAverage(*(ts_sub->get("open")), 3);
    ts_sub->add("open_sma2", sma);
    ts_sub->print();
    return 0;
};

// TODO
// interpolate missing values
// compute standard deviation/ volatility
// GARCH/ ARIMA
// portfolio optimization
// integer programming

// ==>> which libraries to use???