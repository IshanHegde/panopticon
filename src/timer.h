#ifndef TIMER_H
#define TIMER_H
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


struct Timer;

struct Global_Timer{

    struct Timer * timers;
    double total_time;
    size_t num_timers;
};

extern struct Global_Timer* global_timer;

struct Timer{
    clock_t start_time;
    double elapsed_time;
    double total_elapsed_time;
    char * name;
    double time_mean;
    int count;
};



void watch_update(struct Timer * timer);


void alloc_timer(char * name);

void alloc_global_timer();

void watch(char * name);

void free_global_timer();

void print_statistics();

void exit_functions();

#define GLOBAL_TIMER() \
    alloc_global_timer(); \
    atexit(exit_functions);\

#endif 