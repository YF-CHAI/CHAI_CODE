#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include "read_time.h"
#include "instructor.h"

/*
 * check_cpu_features -- validates CPU features detection
 */
static void
check_cpu_features(void)
{
    if (is_cpu_clflush_present()) {
        UT_OUT("CLFLUSH supported");
        _mm_clflush(Buf);
    } else {
        UT_OUT("CLFLUSH not supported");
    }

    if (is_cpu_clflushopt_present()) {
        UT_OUT("CLFLUSHOPT supported");
        _mm_clflushopt(Buf);
    } else {
        UT_OUT("CLFLUSHOPT not supported");
    }

    if (is_cpu_clwb_present()) {
        UT_OUT("CLWB supported");
        _mm_clwb(Buf);
    } else {
        UT_OUT("CLWB not supported");
    }
}


static char test_buffer[4096];
int main()
{

    //memset(test_buffer,'A',4096);
    while(1)
    {
        unsigned long long time_start = asm_rdtscp();
        //printf("Hello World!\n");
        //_mm_clwb(test_buffer);
        asm_clflush(test_buffer);
        //_mm_clflushopt(test_buffer);
        unsigned long long time_end = asm_rdtscp();
        printf("the cost time is: %llu\n",time_end - time_start);
        sleep(1);

    }

    return 0;
}



