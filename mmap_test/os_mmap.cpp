#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <iostream>
#define POBJ_LAYOUT_NAME(name) #name
using namespace std;
int os_mmap_main()
{
  string str = "POBJ_LAYOUT_NAME(hello)";
  cout<<str<<"is the string~"<<endl;
  int fd;
 if ( (fd = open("data.cfg", O_RDWR|O_CREAT, S_IRWXU)) < 0){
  printf("open file wrong!");
  //exit(1);
  return -1;
 }

 struct stat file_stat;
 if ( fstat( fd, &file_stat) < 0 )
 {
  printf(" fstat wrong");
  //exit(1);
  return -1;
 }



 void *start_fp;
 if( ( start_fp = mmap(NULL, file_stat.st_size, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0 )) == MAP_FAILED)
 {
  printf("mmap wrong");
  //exit(0);
  return -1;
 }
  close(fd);
  char* pp = (char*)start_fp;
  //snprintf( (char *)start_fp, 4, "AAAA");
  //msync( start_fp, file_stat.st_size, MS_ASYNC);
  for(int i=0;i<5;i++)
  {
      cout<<"the current char is: "<<*pp<<endl;
      *pp =*pp+0x1;
      pp++;
  }

  if ( munmap( start_fp, file_stat.st_size ) < 0 )
  {
  printf("munmap wrong");
  //exit(1);
  return -1;
  }

    return 0;
}
