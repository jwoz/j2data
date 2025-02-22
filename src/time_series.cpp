//
// Created by j on 2020-06-05.
//

#include "iostream"
#include "time_series.h"
#include "csv.h"
#include "tools.h"
#include <ctime>
#include <map>
#include <utility>

TimeSeries::TimeSeries(map_time_t times, vec_string_t columns, vec_vec_dbl_t data)
        : m_times(std::move(times)), m_columns(std::move(columns)), m_data(std::move(data))
{
}


TimeSeries::TimeSeries(const std::string &filename, const std::string &period)
        : m_columns{"open", "close", "high", "low"}
{
    io::CSVReader<9> in(filename);

    std::string Datetime;
    double Open, High, Low, Close;
    int Volume;
    double Dividends;
    double StockSplits;
    std::string Symbol;

    vec_dbl_t v_open;
    vec_dbl_t v_close;
    vec_dbl_t v_high;
    vec_dbl_t v_low;

    int i = 0;
    in.read_header(io::ignore_extra_column, period == "1d" ? "Date" : "Datetime", "Open", "High", "Low", "Close", "Volume", "Dividends", "Stock Splits", "Symbol");
    while (in.read_row(Datetime, Open, High, Low, Close, Volume, Dividends, StockSplits, Symbol))
    {
        int year = std::stoi(Datetime.substr(0, 4));
        int month = std::stoi(Datetime.substr(5, 7));
        int day = std::stoi(Datetime.substr(8, 10));
        int hour, minute;
        if (period != "1d")
        {
            hour = std::stoi(Datetime.substr(11, 13));
            minute = std::stoi(Datetime.substr(14, 16));
        } else
        {
            hour = minute = 0;
        }
        std::tm dt = {};
        dt.tm_year = year;
        dt.tm_mon = month - 1;
        dt.tm_mday = day;
        dt.tm_hour = hour, dt.tm_min = minute;

        if (m_times.count(dt) > 0)
        {
            std::cout << "WARNING: Time stamp " << Datetime << " already exists. Skipping" << std::endl;
            continue; // TODO option to keep last??
        }
        m_times.insert(std::pair<tm, int>(dt, i));
        v_open.push_back(Open);
        v_close.push_back(Close);
        v_high.push_back(High);
        v_low.push_back(Low);

        ++i;
        m_symbol = Symbol;
    }
    m_data = {v_open, v_close, v_high, v_low};
}

std::unique_ptr<TimeSeries> TimeSeries::range(const tm &t0, const tm &t1) const
{
    auto first = m_times.lower_bound(t0);
    auto last = m_times.upper_bound(t1);

    map_time_t v_times(first, last);
    int i0 = first->second;
    int i1 = last->second;

    std::for_each(v_times.begin(), v_times.end(), [i0](std::pair<const tm, int> &p) { p.second -= i0; });

    vec_vec_dbl_t data;
    for (const auto &it : m_data)
    {
        vec_dbl_t v;
        for (int i = i0; i != i1; ++i)
        {
            v.push_back(it[i]);
        }
        data.push_back(v);
    }

    std::unique_ptr<TimeSeries> ts(new TimeSeries(v_times, m_columns, data));
    return ts;
}


long TimeSeries::count() const
{
    return m_times.size();
}

std::string TimeSeries::symbol() const
{
    return m_symbol;
}

tm TimeSeries::minimum_time() const
{
    return m_times.cbegin()->first;
}

tm TimeSeries::maximum_time() const
{
    return m_times.cend()->first;
}


std::string TimeSeries::asc_minimum_time() const
{
    tm first = m_times.cbegin()->first;
    return to_string_tm(first);
}

std::string TimeSeries::asc_maximum_time() const
{
    tm last = m_times.crbegin()->first;
    return to_string_tm(last);
}

void TimeSeries::print() const
{
    for (const auto &it : m_columns)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;
    for (const auto &it : m_times)
    {
        std::cout << to_string_tm(it.first);
        for (const auto &id : m_data)
        {
            std::cout << " ";
            std::cout << id[it.second];
        }
        std::cout << std::endl;
    }

}

void TimeSeries::add(std::string name, vec_dbl_t data)
{
    m_columns.push_back(std::move(name));
    m_data.push_back(std::move(data));
}

const vec_dbl_t *TimeSeries::get(const std::string &name) const
{
    auto index = findElement<std::string>(m_columns, name);
    if (!index.first)
    {
        std::cout << "ERROR: column " << name << " does not exist in time series." << std::endl;
        return nullptr;
    }
    return &m_data[index.second];
}

