#ifndef READ_TIME_H
#define READ_TIME_H
#include <stdint.h>


uint64_t hrtime_cycles(void)
{
    unsigned hi, lo;
    __asm__ __volatile__ ("rdtscp" : "=a"(lo), "=d"(hi));
    return ( (uint64_t)lo)|(((uint64_t)hi)<<32);
}
#endif // READ_TIME_H
