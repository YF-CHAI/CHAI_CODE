#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include "read_time.h"

int main()
{


        uint64_t time_start = hrtime_cycles();
        printf("Hello World!\n");
        uint64_t time_end = hrtime_cycles();
        printf("the cost time is: %llu\n",time_end - time_start);
        //printf("the cost time is: %llu\n",t_time);
        sleep(1);

    return 0;
}



