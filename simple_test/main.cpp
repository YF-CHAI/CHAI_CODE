#include <stdio.h>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <sys/mman.h>
#include <time.h>
#include <unistd.h>


#define MAX_MMAP_FILE_NUM 10
#define MMAP_FILE_PATH "/mnt/pmem9/"
#define MMAP_FILE_LENGTH 1024*1024*200

using namespace std;

int fd_array[MAX_MMAP_FILE_NUM] = {-1};
string file_list[MAX_MMAP_FILE_NUM];

void
create_files(int f_size,int f_num)
{
    for(int i=0;i<f_num;i++)
    {
        string file_name = to_string(i)+".dat";
        file_list[i] = file_name;
        file_name = MMAP_FILE_PATH + file_name;
        fd_array[i] = open(file_name.c_str(), O_RDWR|O_CREAT, S_IRWXU);
        if(fd_array[i] != -1)
            fallocate(fd_array[i],0,0,f_size);

    }


}


void
close_files(int f_num)
{
    for(int i=0;i<f_num;i++)
        close(fd_array[i]);
}


void
mmap_files(int f_num)
{

}

int
main(int argc, char *argv[])
{
    struct timespec time_start, time_end;
    long long time_fun_run;

    //struct stat file_stat;
    //if ( fstat( fd, &file_stat) < 0 )
    //{
    // printf(" fstat wrong");
    // return -1;
    //}

    //gettimeofday(&time_start , NULL);
    clock_gettime(CLOCK_MONOTONIC,&time_start);//more precise to ns level
    printf("THE FUCTION RUNNING!\n");
    //gettimeofday(&time_end,NULL);
    clock_gettime(CLOCK_MONOTONIC,&time_end);
    time_fun_run = 1e9*(time_end.tv_sec-time_start.tv_sec) + (time_end.tv_nsec -time_start.tv_nsec);
    printf("The fuction spend time is:%lld ns\n",time_fun_run);
    create_files(MMAP_FILE_LENGTH,MAX_MMAP_FILE_NUM);


    close(MAX_MMAP_FILE_NUM);
    cout << "Hello World!" << endl;
    return 0;
}
