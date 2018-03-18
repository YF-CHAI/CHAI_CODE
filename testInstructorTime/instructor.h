#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H


/* Flush cacheline */
#define asm_clflush(addr)                   \
({                              \
    __asm__ __volatile__ ("clflush %0" : : "m"(*addr)); \
})

/* Memory fence */
#define asm_mfence()                \
({                      \
    PM_FENCE();             \
    __asm__ __volatile__ ("mfence");    \
})


/*
 * The x86 memory instructions are new enough that the compiler
 * intrinsic functions are not always available.  The intrinsic
 * functions are defined here in terms of asm statements for now.
 */
#define _mm_clflushopt(addr)\
    asm volatile(".byte 0x66; clflush %0" : "+m" (*(volatile char *)addr));
#define _mm_clwb(addr)\
    asm volatile(".byte 0x66; xsaveopt %0" : "+m" (*(volatile char *)addr));

#endif // INSTRUCTOR_H
