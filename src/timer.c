#include "timer.h"

struct Global_Timer* global_timer = NULL;


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
    timer->CONSTANT_1 = global_timer->resolution;
    timer->CONSTANT_2 = global_timer->resolution/pow(10,9);
}

void watch_update(struct Timer * timer){
    
    clock_gettime(CLOCK_MONOTONIC_RAW, &timer->start_time);
    return;
    //timer->elapsed_time = (timer->current_time.tv_sec - timer->start_time.tv_sec) * global_timer->resolution;
    
    
}

void stop_watch_(struct Timer * timer){
    //printf("RESOLUTION: %f\n",timer->CONSTANT_2);
    clock_gettime(CLOCK_MONOTONIC_RAW, &timer->current_time);
    timer->elapsed_time += (timer->current_time.tv_sec - timer->start_time.tv_sec) * timer->CONSTANT_1 + (timer->current_time.tv_nsec - timer->start_time.tv_nsec)* timer->CONSTANT_2;
    timer->count++;
    
}

void stop_watch(char * name){
    
   int i;
    for (i = 0; i < global_timer->num_timers; i++) {
        if (strcmp(global_timer->timers[i].name, name) == 0){
            
            stop_watch_(&global_timer->timers[i]);
            return;
        }
    }
}


void alloc_global_timer(enum TIME_RESOLUTION resolution){

    global_timer = (struct Global_Timer *)malloc(sizeof(struct Global_Timer));
    global_timer->num_timers =0;
    global_timer->timers =NULL;
    global_timer->total_time =0.0;
    global_timer->resolution = resolution;
}



void watch(char * name){
    
    int i;
    for (i = 0; i < global_timer->num_timers; i++) {
        if (strcmp(global_timer->timers[i].name, name) == 0){
            
            watch_update(&global_timer->timers[i]);
            return;
        }
    }
    
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

    for (int i=0;i<global_timer->num_timers;i++){
        global_timer->timers[i].time_mean =(double) global_timer->timers[i].elapsed_time/global_timer->timers[i].count;
        printf("%s: \n",global_timer->timers[i].name);
        printf("Total Time: %ld\n",global_timer->timers[i].elapsed_time);
        printf("Average Time: %.1f\n",global_timer->timers[i].time_mean);
        printf("Count: %d\n", global_timer->timers[i].count);
    }
}

void exit_functions(){
    print_statistics();
    free_global_timer();
}