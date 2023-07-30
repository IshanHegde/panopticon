#include "timer.h"


void alloc_timer(struct Global_Timer *global_timer, char *name) {
    global_timer->num_timers++;
    global_timer->timers = (struct Timer*) realloc(global_timer->timers, global_timer->num_timers * sizeof(struct Timer));
    struct Timer *timer = &(global_timer->timers[global_timer->num_timers - 1]);
    timer->name = (char*) malloc(strlen(name) + 1);
    strcpy(timer->name, name);
    timer->start_time = clock();
    timer->elapsed_time = 0.0;
    timer->start_time = 0;
    timer->time_mean = 0.0;
    timer->count = 1;
    timer->total_elapsed_time = 0.0;
}

void watch_update(struct Timer * timer){
    
    timer->elapsed_time = (double)(clock() - timer->total_elapsed_time) / CLOCKS_PER_SEC;
    timer->total_elapsed_time += timer->elapsed_time;
    timer->count++;
    timer->time_mean = timer->total_elapsed_time/timer->count;
}

struct Global_Timer * alloc_global_timer(){

    struct Global_Timer * global_timer = (struct Global_Timer *)malloc(sizeof(struct Global_Timer));
    global_timer->num_timers =0;
    global_timer->timers =NULL;
    global_timer->total_time =0.0;
    return global_timer;
}



void watch(struct Global_Timer * global_timer,char * name){

    int i;
    for (i = 0; i < global_timer->num_timers; i++) {
        if (strcmp(global_timer->timers[i].name, name) == 0){
            watch_update(&global_timer->timers[i]);
            return;
        }
    }

    alloc_timer(global_timer,name);
    
}

void free_global_timer(struct Global_Timer * global_timer){

    for (int i=0;i<global_timer->num_timers;i++){
        free(global_timer->timers[i].name);
    }
    free(global_timer->timers);

    free(global_timer);
}

void print_statistics(struct Global_Timer * global_timer){

    for (int i=0;i<global_timer->num_timers;i++){
        printf("%s: \n",global_timer->timers[i].name);
        printf("Total Time: %f\n",global_timer->timers[i].total_elapsed_time);
        printf("Average Time: %f\n",global_timer->timers[i].time_mean);
        printf("Count: %d\n", global_timer->timers[i].count);
    }
}