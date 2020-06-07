//
// Created by j on 2020-06-07.
//

#include "operate.h"

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