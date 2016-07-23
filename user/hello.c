#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define MAX 50

int
main(int argc, char *argv[])
{
  int fd = open("foo.txt", O_CREATE|O_RDWR|O_SMALLFILE);
  //int ec = open("echo.c", O_RDWR);
  //printf(1, "hello %d\n", fd);
  //char buf = 'a';
  char buf[2] = "xy";
  write(fd, &buf, 2);
  //can we write and read it back from SMALLFILE
  //void* newbuf = NULL;
  close(fd);
  int fh = open("foo.txt", O_RDONLY);
  char newbuf[10];
  int bytesRead = read(3, newbuf, 2);
  //newbuf[bytesRead] = '\0';
  printf(1, "here's the read stuff: %s (bytesRead: %d), (device: %d)\n", newbuf, bytesRead, fh);
  close(fh);

  char buf3[MAX];
  char buf4[MAX];

  int i=0;

  for(i = 0; i < MAX; i++){
    buf3[i] = (char)(i+(int)'0');
    //printf(1, "i=%d, buf3[i]=%s\n", i, buf3[i]);
  }

  int fd2 = -1;

  if((fd2 = open("test_file.txt", O_CREATE | O_SMALLFILE)) < 0){
    printf(1, "Failed to create a small file\n");
  }
  close(fd2);

  if((fd2 = open("test_file.txt", O_RDWR)) < 0){
    printf(1, "Failed to open a small file\n");
  }

  if(write(fd2, buf3, MAX) != MAX){
    printf(1, "Write failed!\n");
  }
  close(fd2);
  
  if((fd2 = open("test_file.txt", O_RDWR)) < 0){
    printf(1, "Failed to open a small file\n");
  }

  if(read(fd2, buf4, MAX) != MAX){
    printf(1, "Read failed!\n");
  }
  close(fd2);

  printf(1, "buf4=%s\n", buf4);
  for(i = 0; i < MAX; i++){
    printf(1, "i=%d, buf3[i]=%s, buf4[i]=%s\n", i, buf3+i, buf4+i);
  }

  exit();
}
