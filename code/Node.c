#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

int main(int argc, char* argv[]) {
    /* expects at least 1 argument node number*/
    if (argc > 1) {
        /* open file */
        /* part with benchmark?? */
        
        /* while not EOF */
        /* getc to get workload */

        /* sleep 1/benchmark */
    } else {
        printf("not enough program arguments");
    }
}