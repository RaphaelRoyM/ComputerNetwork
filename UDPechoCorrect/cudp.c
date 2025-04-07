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
  struct sockaddr_in servaddr;
  socklen_t servlen=sizeof(servaddr);
  
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(port);
  servaddr.sin_addr.s_addr=INADDR_ANY;
  
  memset(buffer,'\0',sizeof(buffer));
  
  printf("enter a string \t");
  //scanf("%s",buffer);
  fgets(buffer,sizeof(buffer),stdin);
  printf("entered string %s\n",buffer);  
  
  
  int n=sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&servaddr,servlen);
  memset(buffer,'\0',sizeof(buffer));
  n=recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&servaddr,&servlen);
  printf("received string is %s\n",buffer);
  close(sockfd);
  return 0;
}
