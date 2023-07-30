#include <stdio.h>
#include "timer.h"
#include <unistd.h>
int main(){
    
    
    //struct Global_Timer* timer = alloc_global_timer();
    GLOBAL_TIMER(NANOSECONDS)
    WATCH("main")
    int j =0;

    for (int i= 0;i<10;i++){
        WATCH("outer_loop")
        
        j+=rand()%2;
        for (int k=0;k<1000000;k++){
            WATCH("inner_loop")
            j+=rand()%7;
            STOP_WATCH("inner_loop")
        }
        STOP_WATCH("outer_loop")
    }
    STOP_WATCH("main")
    //print_statistics(timer);

    //free_global_timer(timer);
    //print_statistics();
    return 0;
}

