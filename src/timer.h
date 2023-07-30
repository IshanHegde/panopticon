#ifndef TIMER_H
#define TIMER_H
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>
#include <math.h>


#define WATCH(name) watch(name);

#define STOP_WATCH(input_name) \
    for (int i = 0; i < global_timer->num_timers; i++) {\
        if (strcmp(global_timer->timers[i].name, input_name) == 0){\
            watch_stop(&global_timer->timers[i]);\
            break;\
        }\
    };\

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
    uint64_t CONSTANT_1;
    double CONSTANT_2;
};

extern struct Global_Timer* global_timer;

struct Timer{
    struct timespec start_time;
    struct timespec current_time;
    uint64_t elapsed_time;
    char * name;
    double time_mean;
    int count;
};


void watch_update(struct Timer * timer);

void watch_stop(struct Timer * timer);

void alloc_timer(char * name);

void alloc_global_timer(enum TIME_RESOLUTION resolution);

void watch(char * name);

void free_global_timer();

void print_statistics();

void exit_functions();

#define GLOBAL_TIMER(resolution) \
    alloc_global_timer(resolution); \
    atexit(exit_functions);\

#endif 