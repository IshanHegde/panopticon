#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
struct Timer;

#define WATCH_START(t) (t).start_time = clock()

#define WATCH_STOP(t) (t).elapsed_time = (double)(clock() - (t).start_time) / CLOCKS_PER_SEC

#define WATCH_RESET(t) (t).elapsed_time = 0; (t).start_time = 0

//#define WATCH(name) t = alloc_timer(name);

//#define PROGRAM_TIMER(name) struct Global_Timer* timer = alloc_global_timer();

//#define PROGRAM_TIMER::WATCH(name) timer.

#define WATCH_UPDATE(t) (t).total_elapsed_time += (t).elapsed_time; (t).count++; (t).time_mean = (t).total_elapsed_time /(t).count;

struct Timer{
    clock_t start_time;
    double elapsed_time;
    double total_elapsed_time;
    char * name;
    double time_mean;
    int count;
};



void watch_update(struct Timer * timer);

struct Global_Timer{

    struct Timer * timers;
    double total_time;
    size_t num_timers;
};

void alloc_timer(struct Global_Timer * global_timer, char * name);

struct Global_Timer * alloc_global_timer();

void watch(struct Global_Timer * global_timer,char * name);

void free_global_timer(struct Global_Timer * global_timer);

void print_statistics(struct Global_Timer * global_timer);