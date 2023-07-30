#include <stdio.h>
#include "timer.h"

int main(){
    
    
    struct Global_Timer* timer = alloc_global_timer();
    watch(timer,"main");
    int j =0;

    for (int i= 0;i<10;i++){
        watch(timer,"loop_function");

        j+=120;
        
    }

    print_statistics(timer);

    free_global_timer(timer);

    return 0;
}