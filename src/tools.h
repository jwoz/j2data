
#ifndef J2DATA_TOOLS_H
#define J2DATA_TOOLS_H

#include <ctime>
#include <string>

tm create_tm(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);
std::string to_string_tm(const tm &t);

template<typename T>
std::pair<bool, int> findElement(const std::vector<T> &vec, const T &element);


#endif