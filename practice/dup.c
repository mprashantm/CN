#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main()
{
 int fd=open("a.txt",O_RDWR);
 close(0);
 dup2(fd,0);
 char ch[5];
// read(fd,ch,5);
 scanf("%s",ch),
 printf("%s",ch);
  scanf("%s",ch),
 printf("%s",ch);
 scanf("%s",ch),
 printf("%s",ch);
 scanf("%s",ch),
 printf("%s",ch);
 scanf("%s",ch),
 printf("%s",ch);

}
