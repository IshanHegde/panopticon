#include <panopticon.h>

int main(){

    GLOBAL_TIMER(NANOSECONDS,CLOCK_PROCESS_CPUTIME_ID)
    WATCH("main")

    for(int i = 0; i < 1000000; i++){
        WATCH("loop")
        STOP_WATCH("loop")
    }

    STOP_WATCH("main")

    return 0;
}