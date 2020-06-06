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

    auto ts_daily = make_shared<TimeSeries>("data/timeseries_1d.csv");
    auto ts_60min = make_shared<TimeSeries>("data/timeseries_60m.csv", "60m");


};

    // TODO
// read a csv file
// compute a moving average
// interpolate missing values
// compute standard deviation/ volatility

// portfolio optimization
// integer programming

// ==>> which libraries to use???