#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#define PORT 5000
int main(){
  struct sockaddr_in serv_addr,client_addr;
  socklen_t servsize=sizeof(serv_addr);
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
    
  printf("enter the 1st number\t");
  scanf("%d",&n1);
  printf("enter the 2nd number\t");
  scanf("%d",&n2);
  
  sendto(sockfd,&n1,sizeof(n1),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
  sendto(sockfd,&n2,sizeof(n2),0,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
  
  recvfrom(sockfd,&sum,sizeof(sum),0,(struct sockaddr*)&serv_addr,&servsize);
  printf("the sum is %d \n",sum);
  close(sockfd);
}
