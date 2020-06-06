//
// Created by j on 2020-06-05.
//

#include "iostream"
#include "time_series.h"
#include "csv.h"
#include <ctime>
#include <map>


TimeSeries::TimeSeries(const std::string &filename, const std::string &period) {
    io::CSVReader<9> in(filename);
    in.read_header(io::ignore_extra_column, period == "1d" ? "Date" : "Datetime", "Open", "High", "Low", "Close", "Volume", "Dividends", "Stock Splits", "Symbol");
    std::string Datetime;
    double Open, High, Low, Close;
    int Volume;
    double Dividends;
    double StockSplits;
    std::string Symbol;
    int i = 0;
    while (in.read_row(Datetime, Open, High, Low, Close, Volume, Dividends, StockSplits, Symbol)) {
        int year = std::stoi(Datetime.substr(0, 4));
        int month = std::stoi(Datetime.substr(5, 7));
        int day = std::stoi(Datetime.substr(8, 10));
        int hour, minute;
        if (period != "1d") {
            hour = std::stoi(Datetime.substr(11, 13));
            minute = std::stoi(Datetime.substr(14, 16));
        } else {
            hour = minute = 0;
        }
        std::tm dt;
        dt.tm_year = year;
        dt.tm_mon = month - 1;
        dt.tm_mday = day;
        dt.tm_hour = hour, dt.tm_min = minute;
//        std::cout << Datetime << " " << dt.tm_year << " " << month << std::endl;

        if (m_times.count(dt)>0) {
            std::cout << "WARNING: Time stamp " << Datetime << " already exists. Skipping" << std::endl;
            continue; // TODO option to keep last??
        }
        m_times.insert(std::pair<tm, int>(dt, i));
        m_open.push_back(Open);
        m_close.push_back(Close);
        m_high.push_back(High);
        m_low.push_back(Low);

        m_symbol = Symbol;
    }
}

long TimeSeries::count() const {
    return m_times.size();
}
std::string TimeSeries::symbol() const {
    return m_symbol;
}