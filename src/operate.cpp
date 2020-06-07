//
// Created by j on 2020-06-07.
//

#include "operate.h"

typedef std::vector<double> dbl_vec_t;

dbl_vec_t movingAverage(dbl_vec_t &prices, uint p)
{
    auto n = prices.size();
    if (prices.size() - p < 0)
        return dbl_vec_t();
    uint sizeOfAverages = n - p + 1;

    // allocate
    dbl_vec_t averages(n, 0);
    uint m = 0;
    double sum = 0;
    for (uint k = 0; k < n; ++k)
    {
        sum += prices[k];
        if (k <= p)
        {
            ++m;
            averages[k] = sum / m; // first p until window size reached
            continue;
        }
        sum -= prices[k - p];
        averages[k] = sum / m;
    }
    return averages;
}
