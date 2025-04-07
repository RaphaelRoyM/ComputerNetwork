#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define port 9001
int main(){
  char buffer[100];
  int sockfd=socket(AF_INET,SOCK_DGRAM,0);
  if(sockfd<0){
    printf("sockect error\n");
    exit(1);
  }
  struct sockaddr_in servaddr,cliaddr;
  socklen_t clilen=sizeof(cliaddr);
  socklen_t servlen=sizeof(servaddr);
  
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(port);
  servaddr.sin_addr.s_addr=INADDR_ANY;
  
  bind(sockfd,(struct sockaddr*)&servaddr,servlen);
  memset(buffer,'\0',sizeof(buffer));
  int n=recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,&clilen);
  n=sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&cliaddr,clilen);
  close(sockfd);
  return 0;
}
