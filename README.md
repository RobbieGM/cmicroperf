# cmicroperf

Cmicroperf is a simple macro-based profiler for C code that measures wall-clock time taken to execute specified blocks or lines of code. It can be useful for situations (IO-bound or network-bound calls) where measuring elapsed time is more useful than measuring CPU cycles or CPU time, which tools like `perf` do.

## Usage

```c 
#include "cmicroperf.h"

int main(int arg, char **argv) {
    // Start the profiler thread
    pthread_t profiler_thread;
    pthread_create(&profiler_thread, NULL, start_profiler_output_writer, NULL);

    // ...

    PROFILE(do_long_task());
}
```

The profiler will write its output once per second to cmicroperf.out in the current directory. In this output file, each line will contain a source line number and a total number of microseconds elapsed inside the `PROFILE()` macro on that line.
