# Panopticon

Panopticon is a simple instrumentation timer library designed to accurately measure the time taken by any code block in a C/C++ program.


By inserting lightweight instrumentation code using Panopticon's macros, the duration of code blocks, along with other statistics, can be precisely measured  without altering program logic. 

Jump to: [Installing](#installing)

# Usage



```c
// This will initialize the global timer that will print time in Milliseconds and use a Wall time clock
GLOBAL_TIMER(MICROSECONDS,CLOCK_MONOTONIC)
    
srand(time(NULL));

// measure sleep time 
WATCH("sleep_time")
sleep(1);
STOP_WATCH("sleep_time")

int j =0;

for (int i =0;i< 100000;i++){
    // Measure the timings of the outer loop
    WATCH("outer_loop")

    j+=4 +rand()%5 +9;

    for (int k =0;k<40;k++){
        // Measure the timings of the inner loop
        WATCH("inner_loop")

        j += rand() %4 +1;
        
        // End of inner loop
        STOP_WATCH("inner_loop")
    }
    // End of outer loop
    STOP_WATCH("outer_loop")
}

```
## Output
```bash
--------------------------------------------------------------------------------
| Timer Name           |   Total Time (us)|    Avg. Time (us)|           Count |
--------------------------------------------------------------------------------
| sleep_time           |        1000098.3 |      1000098.323 |               1 |
--------------------------------------------------------------------------------
| outer_loop           |         201758.0 |            2.018 |          100000 |
--------------------------------------------------------------------------------
| inner_loop           |         112033.4 |            0.028 |         4000000 |
--------------------------------------------------------------------------------
```
## Details

The timer will always measure the time in nanosecond resolution. The resolution passed below is just for how the results are displayed.

The timer was measured to take ```~540``` nanoseconds on average ```(N=100,000)``` to measure the time of an empty code block on ```Ryzen 9 6900HX```, ```16 GB RAM``` and ```Ubuntu 22.04 LTS```. 

This time is only of concern if nested timers are used as shown above. **Only the outer loop will be affected by this overhead.**

The Global Timer will be deallocated automatically when the main block is exited using the ```atexit``` function. The statistics will also be printed to the terminal here.

# Installing 

## Requirements

- POSIX 
- gcc 
- g++ 
- CMake 

Unfortunately, this has been only tested to work on Linux. Portability is on the TODO list.

## Using the library 

1. Get the contents of /src

2. Either directly include the source file or configure CMake to import this as a library:
```CMake

# change src/ to where panopticon.c is
set(LIBRARY_SOURCES src/panopticon.c)

add_library(panopticon ${LIBRARY_SOURCES})


target_include_directories(panopticon PUBLIC src)

# change example_c 
add_executable(example_c examples/example_c.c)
target_link_libraries(example_c PRIVATE panopticon)
```
Be sure to compile with ```-std=gnuXX``` where ```XX``` is the C Version. 

# TODO

- MacOS Portability 
- Windows Protability 
- Reduce the timer overhead 
- Add options for more statistics
