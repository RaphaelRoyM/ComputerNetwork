#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORT 5000
int main(){
  struct sockaddr_in serv_addr,client_addr;
  socklen_t clientsize=sizeof(client_addr);
  int n1,n2,sum;
  int sockfd=socket(AF_INET,SOCK_DGRAM,0);
  if(sockfd<0){
  perror("socket error\n");
  exit(1);
  }
  printf("socket created\n");
  serv_addr.sin_family=AF_INET;
  serv_addr.sin_port=htons(5000);
  serv_addr.sin_addr.s_addr=INADDR_ANY;
  int b=bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
  if(b<0){
    perror("bind error\n");
    exit(1);
  }
  printf("bind successfull. bind value is %d\n",b);
  recvfrom(sockfd,&n1,sizeof(n1),0,(struct sockaddr*)&client_addr,&clientsize);
  recvfrom(sockfd,&n2,sizeof(n2),0,(struct sockaddr*)&client_addr,&clientsize);
  printf("n1 is %d and n2 is %d\n",n1,n2);
  sum=n1+n2;
  printf("the sum is %d\n",sum);
  
  sendto(sockfd,&sum,sizeof(sum),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
  close(sockfd);
  
}
