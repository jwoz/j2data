//
// Created by j on 2020-06-07.
//

#ifndef J2DATA_OPERATE_H
#define J2DATA_OPERATE_H

#include "types.h"

vec_dbl_t simpleMovingAverage(const vec_dbl_t & values, uint p);
vec_dbl_t exponentialMovingAverage(const vec_dbl_t & values, double alpha);


#endif //J2DATA_OPERATE_H
