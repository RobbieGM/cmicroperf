#include "cmicroperf.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef WINDOWS
#include <windows.h>
#else
#include <unistd.h>
#endif

struct Record {
  char *file;
  unsigned int line;
  unsigned long long time;
};

size_t cmicroperf_num_records = 0;
struct Record cmicroperf_records[MAX_RECORDS] = {0};

void *cmicroperf_start_output_writer(void *_) {
  while (1) {
    FILE *file = fopen("lineperf.out", "w");
    for (int i = 0; i < cmicroperf_num_records; i++) {
      struct Record record = cmicroperf_records[i];
      fprintf(file, "%s:%d: %llu microseconds\n", record.file, record.line,
              record.time);
    }
    fclose(file);
    sleep(1);
  }
  return NULL;
}

void cmicroperf_record(char *file, unsigned int line, unsigned long long time) {
  int exists = 0;
  for (int i = 0; i < cmicroperf_num_records; i++) {
    struct Record *record = &cmicroperf_records[i];
    // Might be able to compare pointers directly instead of with strcmp
    if (file == record->file && line == record->line) {
      exists = 1;
      record->time += time;
    }
  }
  if (!exists) {
    struct Record new_record = {.file = file, .line = line, .time = time};
    cmicroperf_records[cmicroperf_num_records++] = new_record;
  }
}
