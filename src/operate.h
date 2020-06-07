//
// Created by j on 2020-06-07.
//

#ifndef J2DATA_OPERATE_H
#define J2DATA_OPERATE_H

#include "types.h"

vec_dbl_t simpleMovingAverage(const vec_dbl_t & values, uint p);
vec_dbl_t exponentialMovingAverage(const vec_dbl_t & values, double alpha);
vec_dbl_t logReturn(const vec_dbl_t &values);

vec_dbl_t standardDeviation(const vec_dbl_t &values, uint p);
vec_dbl_t volatility(const vec_dbl_t & values, uint p);

#endif //J2DATA_OPERATE_H
