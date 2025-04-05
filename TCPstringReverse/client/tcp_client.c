#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#define PORT 9001
int main(){
  int sock_desc=socket(AF_INET,SOCK_STREAM,0);
  if(sock_desc<0){
    printf("socket error\n");
    return -1;
  }
  struct sockaddr_in servaddr;
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(PORT);
  servaddr.sin_addr.s_addr=INADDR_ANY;
  
  if(connect(sock_desc,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
    printf("bind error\n");
    return -1;
  }
  char buffer[256];
  printf("enter the string to reverse :\t");
  scanf("%s",buffer);
  int wr=write(sock_desc,buffer,strlen(buffer));
  
  int rd=read(sock_desc,buffer,sizeof(buffer));
  printf("the reversed string is : %s\n",buffer);
  close(sock_desc);
  
}
