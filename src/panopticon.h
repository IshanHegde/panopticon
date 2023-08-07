#ifndef PANOPTICON_H
#define PANOPTICON_H

#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#ifdef __cplusplus
extern "C"
{
#endif

#define WATCH(name) watch(name);

#define STOP_WATCH(name) stop_watch(name);
    


enum TIME_RESOLUTION{
    SECONDS         =         1,
    MILLISECONDS    =         1000,
    MICROSECONDS    =         1000000,
    NANOSECONDS     =         1000000000
};

struct Timer;

struct Global_Timer{

    struct Timer * timers;
    double total_time;
    size_t num_timers;
    enum TIME_RESOLUTION resolution;
    clockid_t clock_type;
};

extern struct Global_Timer global_timer;

struct Timer{
    struct timespec start_time;
    uint64_t elapsed_time;
    char * name;
    double time_mean;
    int count;
};

void alloc_global_timer(enum TIME_RESOLUTION resolution,clockid_t clock_type);

// This updates the Timer's start_time 
void watch_start_update(struct Timer * timer,const struct timespec * watch_time);

// This updates the Timer's elapsed_time
void watch_stop_update(struct Timer * timer, const struct timespec * watch_time);

void alloc_timer(const char * name, const struct timespec * watch_time);

void watch(const char * name);

void stop_watch(const char * name);

void free_global_timer();

void print_statistics();

void exit_functions();

#define GLOBAL_TIMER(resolution, clock_type) \
    alloc_global_timer(resolution, clock_type); \
    atexit(exit_functions);\

#ifdef __cplusplus
}
#endif

#endif // PANOPTICON_H