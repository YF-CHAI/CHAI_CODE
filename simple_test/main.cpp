#include <stdio.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>


#define MAX_MMAP_FILE_NUM 10
#define MMAP_FILE_PATH "/mnt/pmem9/"
#define MMAP_FILE_LENGTH 1024*1024*200
using namespace std;

static int fd_array[MAX_MMAP_FILE_NUM] = {-1};

void create_files(int f_size,int f_num)
{


}

int main(int argc, char *argv[])
{
    struct timespec time_start, time_end;
    long long time_fun_run;
    //gettimeofday(&time_start , NULL);
    clock_gettime(CLOCK_MONOTONIC,&time_start);
    printf("THE FUCTION RUNNING!\n");
    //gettimeofday(&time_end,NULL);
    clock_gettime(CLOCK_MONOTONIC,&time_end);
    time_fun_run = 1e9*(time_end.tv_sec-time_start.tv_sec) + (time_end.tv_nsec -time_start.tv_nsec);
    printf("The fuction spend time is:%lld ns\n",time_fun_run);


    string file_name = "data.cfg";
    struct stat file_stat;
    int fd;
    fd = open(file_name.c_str(), O_RDWR|O_CREAT, S_IRWXU);



    cout << "Hello World!" << endl;
    return 0;
}
