#include "cmicroperf.h"
#include <pthread.h>
#include <stdio.h>
#ifdef WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#endif

void testFunc() {
  // This gets optimized out unless using -O0
  for (long long i = 0; i < 100000000; ++i)
    ;
}

int main() {
  pthread_t pth;
  printf("Starting cmicroperf\n");
  pthread_create(&pth, NULL, cmicroperf_start_output_writer, NULL);

  // Use PROFILE on a looping function to test
  for (int i = 0; i < 10; ++i) {
    printf("Running testFunc\n");
    PROFILE(testFunc());
  }
  // Wait at least one extra second to give cmicroperf time to write out
  sleep(1);

  return 0;
}
