//
// Created by j on 2020-06-05.
//

#include "iostream"
#include "time_series.h"
#include "csv.h"

TimeSeries::TimeSeries(const std::string &filename, const std::string &period) {
    io::CSVReader<9> in(filename);
    in.read_header(io::ignore_extra_column, period == "1d" ? "Date" : "Datetime", "Open", "High", "Low", "Close", "Volume", "Dividends", "Stock Splits", "Symbol");
    std::string Datetime;
    double Open, High, Low, Close;
    int Volume;
    double Dividends;
    double StockSplits;
    std::string Symbol;
    while (in.read_row(Datetime, Open, High, Low, Close, Volume, Dividends, StockSplits, Symbol)) {
        std::string year = Datetime.substr(0, 4);
        std::cout << Datetime << " " << year << std::endl;
        m_open.push_back(Open);
        m_close.push_back(Close);
        m_high.push_back(High);
        m_low.push_back(Low);
    }
}

