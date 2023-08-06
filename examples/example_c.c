#include <panopticon.h>

int main(){

    GLOBAL_TIMER(MILLISECONDS,CLOCK_PROCESS_CPUTIME_ID)
    WATCH("main")
    srand(time(NULL));
    
    int j =0;

    for (int i =0;i< 100000;i++){
        WATCH("outer_loop")

        j+=4 +rand()%5 +9;

        for (int k =0;k<40;k++){
            WATCH("inner_loop")

            j += rand() %4 +1;
            
            STOP_WATCH("inner_loop")
        }
        STOP_WATCH("outer_loop")
    }

    STOP_WATCH("main")
    return 0;
}