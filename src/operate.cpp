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
        {
            ++m;
            averages[k] = sum / m; // first p until window size reached
            continue;
        }
        sum -= values[k - p];
        averages[k] = sum / m;
    }
    return averages;
}
