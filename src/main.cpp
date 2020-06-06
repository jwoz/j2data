//
// Created by j on 2020-06-05.
//
#include <iostream>
#include <ctime>
#include "time_series.h"
#include <memory>

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
    std::cout << ts_daily->symbol() << ": " << ts_daily->count() << " daily quotes: " << std::endl;

};

// TODO
// compute a moving average
// interpolate missing values
// compute standard deviation/ volatility
// GARCH/ ARIMA
// portfolio optimization
// integer programming

// ==>> which libraries to use???class tm_compare {
//    constexpr bool operator()(const std::tm & lhs, const std::tm & rhs) const {
//        if (lhs.tm_year < rhs.tm_year) return true;
//        if (lhs.tm_year > rhs.tm_year) return false;
//        if (lhs.tm_mon < rhs.tm_mon) return true;
//        if (lhs.tm_mon > rhs.tm_mon) return false;
//        if (lhs.tm_mday < rhs.tm_mday) return true;
//        if (lhs.tm_mday > rhs.tm_mday) return false;
//        if (lhs.tm_hour < rhs.tm_hour) return true;
//        if (lhs.tm_hour > rhs.tm_hour) return false;
//        if (lhs.tm_min < rhs.tm_min) return true;
//        if (lhs.tm_min > rhs.tm_min) return false;
//        return false;
//    };
//};