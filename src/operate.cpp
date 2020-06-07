//
// Created by j on 2020-06-07.
//

#include "operate.h"
#include <cmath>
#include <cassert>

vec_dbl_t simpleMovingAverage(const vec_dbl_t &values, uint p)
{
    auto n = values.size();
    if (values.size() - p < 0)
        return vec_dbl_t();
    vec_dbl_t averages(n, 0);
    uint m = 0;
    double sum = 0;
    for (uint k = 0; k < n; ++k)
    {
        sum += values[k];
        if (k < p)
            ++m;
        else
            sum -= values[k - p];
        averages[k] = sum / m;
    }
    return averages;
}

vec_dbl_t exponentialMovingAverage(const vec_dbl_t &values, double alpha)
{
    auto n = values.size();
    vec_dbl_t averages(n, 0);
    averages[0] = values[0];
    for (uint k = 1; k < n; ++k)
    {
        averages[k] = alpha * averages[k - 1] + (1.0 - alpha) * values[k];
    }
    return averages;
}

vec_dbl_t logReturn(const vec_dbl_t &values)
{
    auto n = values.size();
    vec_dbl_t logReturns(n, 0);
    for (uint k = 1; k < n; ++k)
    {
        logReturns[k] = log(values[k - 1] / values[k]);
    }
    return logReturns;
}

vec_dbl_t covariance(const vec_dbl_t &v1, const vec_dbl_t &v2, uint p)
{
    auto n = v1.size();
    assert(n == v2.size());
    vec_dbl_t s1 = simpleMovingAverage(v1, p);
    vec_dbl_t s2 = simpleMovingAverage(v2, p);

    vec_dbl_t covariances(n, 0);
    for (uint k = 0; k < n; ++k)
    {
        double sum = 0;
        for (uint kk = ((int) (k + 1 - p) < 0 ? 0 : k + 1 - p); kk <= k; ++kk)
            sum += (v1[kk] - s1[k]) * (v2[kk] - s2[k]);
        covariances[k] = sum / (k + 1 < p ? k + 1 : p);
    }
    return covariances;
}

vec_dbl_t standardDeviation(const vec_dbl_t &values, uint p)
{
    auto n = values.size();
    if (values.size() - p < 0)
        return vec_dbl_t();
    vec_dbl_t stddev(n, 0);
    uint m = 0;
    double sum = 0;
    double squared_sum = 0;
    for (uint k = 0; k < n; ++k)
    {
        sum += values[k];
        squared_sum += values[k] * values[k];
        if (k < p)
            ++m;
        else
        {
            sum -= values[k - p];
            squared_sum -= values[k - p] * values[k - p];
        }
        stddev[k] = sqrt(squared_sum / m - (sum / m) * (sum / m));
    }
    return stddev;
}

vec_dbl_t volatility(const vec_dbl_t &values, uint p)
{
    // TODO annualization.. need to pass vector of times too, aka the timeseries index.
    vec_dbl_t log_returns = logReturn(values);
    vec_dbl_t volatilities = standardDeviation(log_returns, p);
    return volatilities;
}
