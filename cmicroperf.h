#pragma once
#include <time.h>

#define MAX_RECORDS 256

#define PROFILE(x)                                                             \
  do {                                                                         \
    struct timespec start, end;                                                \
    clock_gettime(CLOCK_MONOTONIC, &start);                                    \
    x;                                                                         \
    clock_gettime(CLOCK_MONOTONIC, &end);                                      \
    cmicroperf_record(__FILE__, __LINE__,                                      \
                      end.tv_sec * 1e6 + end.tv_nsec / 1e3 -                   \
                          (start.tv_sec * 1e6 + start.tv_nsec / 1e3));         \
  } while (0)

void *cmicroperf_start_output_writer(void *);
// This function is only intended to be used by the PROFILE macro
void cmicroperf_record(char *file, unsigned int line, unsigned long long time);
