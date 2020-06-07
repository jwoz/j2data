set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable (j2data main.cpp portfolio.cpp portfolio.h time_series.cpp time_series.h csv.h types.h tools.cpp tools.h)
target_link_libraries(j2data Threads::Threads)
