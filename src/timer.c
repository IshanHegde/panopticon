#include "timer.h"

struct Global_Timer* global_timer = NULL;

void alloc_global_timer(enum TIME_RESOLUTION resolution){

    global_timer = (struct Global_Timer *)malloc(sizeof(struct Global_Timer));
    global_timer->num_timers =0;
    global_timer->timers =NULL;
    global_timer->total_time =0.0;
    global_timer->resolution = resolution;
}

void alloc_timer(char *name) {

    global_timer->num_timers++;
    global_timer->timers = (struct Timer*) realloc(global_timer->timers, global_timer->num_timers * sizeof(struct Timer));
    struct Timer *timer = &(global_timer->timers[global_timer->num_timers - 1]);
    clock_gettime(CLOCK_MONOTONIC_RAW, &timer->start_time);
    timer->name = (char*) malloc(strlen(name) + 1);
    strcpy(timer->name, name);
    timer->elapsed_time = 0;
    timer->time_mean = 0.0;
    timer->count = 0;
}

void watch_update(struct Timer * timer){

    clock_gettime(CLOCK_MONOTONIC_RAW, &timer->start_time);    
}

void watch_stop(struct Timer * timer){

    clock_gettime(CLOCK_MONOTONIC_RAW, &timer->current_time);
    timer->elapsed_time += (timer->current_time.tv_sec - timer->start_time.tv_sec) * 1000000000\
     + (timer->current_time.tv_nsec - timer->start_time.tv_nsec);
    timer->count++;
}


void watch(char * name){
    // Update the timer if it is initialized
    for (int i = 0; i < global_timer->num_timers; i++) {
        if (strcmp(global_timer->timers[i].name, name) == 0){
            
            watch_update(&global_timer->timers[i]);
            return;
        }
    }
    // Initalize the timer if not initialized before
    alloc_timer(name);
    return;
}

void free_global_timer(){

    for (int i=0;i<global_timer->num_timers;i++){
        free(global_timer->timers[i].name);
    }
    free(global_timer->timers);

    free(global_timer);
}

void print_statistics(){

    double unit;
    const char* unit_name;
    switch (global_timer->resolution) {
        case SECONDS:
            unit =  SECONDS;
            unit_name = "s";
            break;
        case MILLISECONDS:
            unit = MILLISECONDS;
            unit_name = "ms";
            break;
        case MICROSECONDS:
            unit = MICROSECONDS;
            unit_name = "us";
            break;
        case NANOSECONDS:
        default:
            unit = NANOSECONDS;
            unit_name = "ns";
            break;
    }

    char separator[76];
    memset(separator, '-', 75);
    separator[75] = '\0';
    printf("%-50s\n", separator);
    printf("| %-20s | %16s (%2s)| %16s (%2s)| %15s |\n", "Timer Name", "Total Time",unit_name, "Avg. Time",unit_name ,"Count");
    printf("%-75s\n", separator);

    for (int i=0;i<global_timer->num_timers;i++){
        global_timer->timers[i].time_mean =(double) global_timer->timers[i].elapsed_time/global_timer->timers[i].count;

        printf("| %-20s | %20.1f | %20.1f | %15d |\n", 
            global_timer->timers[i].name, 
                global_timer->timers[i].elapsed_time / unit, 
                    global_timer->timers[i].time_mean /unit,
                        global_timer->timers[i].count);
        printf("%-75s\n", separator);
    }
}

void exit_functions(){
    print_statistics();
    free_global_timer();
}