#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#define port 9001
int main(){
  struct sockaddr_in servaddr;
  socklen_t len=sizeof(servaddr);
  int n1;
  char value[100];
  int sockfd=socket(AF_INET,SOCK_STREAM,0);
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(port);
  servaddr.sin_addr.s_addr=INADDR_ANY;
  connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
  printf("enter a number to reteive key\t");
  scanf("%d",&n1);  
  write(sockfd,&n1,sizeof(n1));
  memset(value,'\0',sizeof(value));
  read(sockfd,value,sizeof(value));
  close(sockfd);
  printf("%s\n",value);
}
