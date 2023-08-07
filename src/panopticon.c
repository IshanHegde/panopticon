#include <string.h>
#include <stdio.h>
#include <math.h>
#include "panopticon.h"


struct Global_Timer global_timer;


/**
 * Allocate a new global timer with the specified resolution and clock type.
 *
 * @param resolution The time resolution for the timer.
 * @param clock_type The clock type to use for timing measurements.
 *                  Valid values are: @enum{CLOCK_MONOTONIC_RAW, CLOCK_PROCESS_CPUTIME_ID, CLOCK_THREAD_CPUTIME_ID}
 * @return           Void. 
 */
void init_global_timer(enum TIME_RESOLUTION resolution,clockid_t clock_type){

    global_timer.num_timers =0;
    global_timer.timers =NULL;
    global_timer.total_time =0.0;
    global_timer.resolution = resolution;
    global_timer.clock_type = clock_type;
}

void alloc_timer(const char *name,const struct timespec * watch_time) {

    global_timer.num_timers++;
    global_timer.timers =  (struct Timer *) realloc(global_timer.timers, global_timer.num_timers * sizeof(struct Timer));
    struct Timer *timer = &(global_timer.timers[global_timer.num_timers - 1]);
    timer->start_time = *(watch_time);
    timer->name = (char*) malloc(strlen(name) + 1);
    strcpy(timer->name, name);
    timer->elapsed_time = 0;
    timer->time_mean = 0.0;
    timer->count = 0;
}

void watch_start_update(struct Timer * timer, const struct timespec * watch_time){

    timer->start_time = *(watch_time);
}

void watch_stop_update(struct Timer * timer,const struct timespec * watch_time){

    timer->elapsed_time += (watch_time->tv_sec - timer->start_time.tv_sec) * 1000000000\
     + (watch_time->tv_nsec - timer->start_time.tv_nsec);
    timer->count++;
}


void watch(const char * name){
    // record the time first
    struct timespec watch_time;
    clock_gettime(global_timer.clock_type,&watch_time);

    // Update the timer if it is initialized
    for (int i = 0; i < global_timer.num_timers; i++) {
        if (strcmp(global_timer.timers[i].name, name) == 0){
            
            watch_start_update(&global_timer.timers[i],&watch_time);
            return;
        }
    }
    // Initalize the timer if not initialized before
    alloc_timer(name,&watch_time);
    return;
}

void stop_watch(const char * name){
    //record the time first and pass this time to the watch_stop_update function
    struct timespec watch_time;
    clock_gettime(global_timer.clock_type,&watch_time);

    for (int i = 0; i < global_timer.num_timers; i++) {\
        if (strcmp(global_timer.timers[i].name, name) == 0){
            watch_stop_update(&global_timer.timers[i],&watch_time);
            return;
        }
    }
}

void free_global_timer(){

    for (int i=0;i<global_timer.num_timers;i++){
        free(global_timer.timers[i].name);
    }
    free(global_timer.timers);

}

void print_statistics(){

    double unit;
    const char* unit_name;
    switch (global_timer.resolution) {
        case SECONDS:
            unit =  1000*1000*1000;
            unit_name = "s";
            break;
        case MILLISECONDS:
            unit = 1000*1000;
            unit_name = "ms";
            break;
        case MICROSECONDS:
            unit = 1000;
            unit_name = "us";
            break;
        case NANOSECONDS:
        default:
            unit = 1;
            unit_name = "ns";
            break;
    }

    char separator[81];
    memset(separator, '-', 80);
    separator[80] = '\0';
    printf("%-50s\n", separator);
    printf("| %-20s | %12s (%2s)| %12s (%2s)| %15s |\n", "Timer Name", "Total Time",unit_name, "Avg. Time",unit_name ,"Count");
    printf("%-80s\n", separator);

    for (int i=0;i<global_timer.num_timers;i++){
        global_timer.timers[i].time_mean =(double) global_timer.timers[i].elapsed_time/global_timer.timers[i].count;

        printf("| %-20s | %16.1f | %16.3f | %15d |\n", 
            global_timer.timers[i].name, 
                global_timer.timers[i].elapsed_time / unit, 
                    global_timer.timers[i].time_mean / unit,
                        global_timer.timers[i].count);
        printf("%-80s\n", separator);
    }
}

void exit_functions(){
    print_statistics();
    free_global_timer();
}