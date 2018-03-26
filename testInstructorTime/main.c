#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "read_time.h"
#include "instructor.h"


size_t string_to_size(char* str);
char *cpuinfo(char *valname);
int cpu_speed_mhz();

void get_instructor_time_rdtsc_ns(int ins_type, int cpu_mhz);
void get_instructor_time_rdtscp_ns(int ins_type, int cpu_mhz);
static inline uint64_t cycles_to_ns(int cpu_speed_mhz, uint64_t cycles)
{
    return (cycles*1000/cpu_speed_mhz);
}
// caller is responsible for freeing memory allocated by this function
char *cpuinfo(char *valname)
{
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("/proc/cpuinfo", "r");
    if (fp == NULL)
    {
        return NULL;
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        if (strstr(line, valname))
        {
            char *colon = strchr(line, ':');
            int len = colon - line;
            char *buf = malloc(strlen(line) - len);
            strcpy(buf, &line[len + 2]);
            free(line);
            fclose(fp);
            return buf;
        }
    }

    free(line);
    fclose(fp);
    return NULL;
}


// reads current cpu frequency through the /proc/cpuinfo file
// avoid calling this function often
 int cpu_speed_mhz()
{
    size_t val;
    char *str = cpuinfo("cpu MHz");
    val = string_to_size(str);
    free(str);
    return val;
}

size_t string_to_size(char* str)
{
    size_t factor = 1;
    size_t size;
    long   val;
    char*  endptr = 0;

    val = strtoull(str, &endptr, 10);
while(endptr && (endptr - str) < strlen(str) && !isalpha(*endptr)) {endptr++;}

    switch (endptr[0]) {
        case 'K':
        case 'k':
            factor = 1024LLU;
            break;
        case 'M': case 'm':
            factor = 1024LLU*1024LLU;
            break;
        case 'G': case 'g':
            factor = 1024LLU*1024LLU*1024LLU;
            break;
        default:
            factor = 1;
    }
    size = factor * val;
    return size;
}

static char test_buffer[4096];
int main()
{
    enum _INS_TYPE
    {
        CFLUSH_TYPE =0,
        MFENCE = 1,
        SLEEP = 2

    };
    int cpu_mhz = cpu_speed_mhz();
    get_instructor_time_rdtscp_ns(CFLUSH_TYPE,cpu_mhz);
    get_instructor_time_rdtscp_ns(MFENCE,cpu_mhz);
    get_instructor_time_rdtscp_ns(SLEEP,cpu_mhz);

    get_instructor_time_rdtsc_ns(CFLUSH_TYPE,cpu_mhz);
    get_instructor_time_rdtsc_ns(MFENCE,cpu_mhz);
        get_instructor_time_rdtsc_ns(SLEEP,cpu_mhz);




    //memset(test_buffer,'A',4096);



    return 0;
}

void get_instructor_time_rdtscp_ns(int ins_type, int cpu_mhz)
{
		int i;


        unsigned long long cycles_start = 0;
        unsigned long long cycles_end = 0;
        uint64_t result = 0;
        switch (ins_type) {
        case 0:
            for( i =0;i<100;i++)
            {
                cycles_start = asm_rdtscp();
                asm_clflush(test_buffer);
                cycles_end = asm_rdtscp();
                result += cycles_end - cycles_start;


            }
            printf("RDTSCP:the CLFLUSH cost time is: %llu ns\n"\
                   ,cycles_to_ns(cpu_mhz,result/100));

            struct timespec time_start={0,0}, time_end={0,0};
            for( i =0;i<100;i++)
            {
                clock_gettime(CLOCK_REALTIME, &time_start);
                asm_clflush(test_buffer);
                clock_gettime(CLOCK_REALTIME, &time_end);
                //result += cycles_end - cycles_start;
                printf("RDTSCP:the CLFLUSH cost time is:%llus %lluns\n", \
                       time_end.tv_sec-time_start.tv_sec, time_end.tv_nsec-time_start.tv_nsec);

            }
            printf("RDTSCP:the CLFLUSH cost time is: %llu ns\n"\
                   ,cycles_to_ns(cpu_mhz,result/100));



            break;
        case 1:
            for( i =0;i<100;i++)
            {
                cycles_start = asm_rdtscp();
                asm volatile ("mfence");
                cycles_end = asm_rdtscp();
                result += cycles_end - cycles_start;


            }
            printf("RDTSCP:the MFENCE cost time is: %llu ns\n"\
                   ,cycles_to_ns(cpu_mhz,result/100));

            break;
        case 2:
            for(i =0;i<100;i++)
            {
                cycles_start = asm_rdtscp();
                sleep(1);
                cycles_end = asm_rdtscp();
                result += cycles_end - cycles_start;


            }
            printf("RDTSCP:the sleep(1) cost time is: %llu ns\n"\
                   ,cycles_to_ns(cpu_mhz,result/100));

            break;
        default:
            break;
        }




}

void get_instructor_time_rdtsc_ns(int ins_type, int cpu_mhz)
{

		int i;
        unsigned long long cycles_start = 0;
        unsigned long long cycles_end = 0;
        uint64_t result = 0;
        switch (ins_type) {
        case 0:
            for( i =0;i<100;i++)
            {
                cycles_start = asm_rdtsc();
                asm_clflush(test_buffer);
                cycles_end = asm_rdtsc();
                result += cycles_end - cycles_start;


            }
            printf("RDTSC:the CLFLUSH cost time is: %llu ns\n"\
                   ,cycles_to_ns(cpu_mhz,result/100));



            break;
        case 1:
            for( i =0;i<100;i++)
            {
                cycles_start = asm_rdtsc();
                asm volatile ("mfence");
                cycles_end = asm_rdtsc();
                result += cycles_end - cycles_start;


            }
            printf("RDTSC:the MFENCE cost time is: %llu ns\n"\
                   ,cycles_to_ns(cpu_mhz,result/100));

            break;
        case 2:
            for( i =0;i<100;i++)
            {
                cycles_start = asm_rdtsc();
                sleep(1);
                cycles_end = asm_rdtsc();
                result += cycles_end - cycles_start;


            }
            printf("RDTSC:the sleep(1) cost time is: %llu ns\n"\
                   ,cycles_to_ns(cpu_mhz,result/100));

            break;
        default:
            break;
        }




}
