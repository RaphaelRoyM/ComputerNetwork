#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#define port 9001
struct KV{
  int key;
  char val[10];
} keyValue[5];


int main(){
  strcpy(keyValue[0].val,"orange");
  keyValue[0].key=25;
  strcpy(keyValue[1].val,"mango");
  keyValue[1].key=26;
  strcpy(keyValue[2].val,"cherry");
  keyValue[2].key=27;
  strcpy(keyValue[3].val,"tomato");
  keyValue[3].key=28;
  strcpy(keyValue[4].val,"pineapple");
  keyValue[4].key=29;

  struct sockaddr_in servaddr;
  socklen_t len=sizeof(servaddr);
  int n1,clisock;
  char value[100];
  int sockfd=socket(AF_INET,SOCK_STREAM,0);
  servaddr.sin_family=AF_INET;
  servaddr.sin_port=htons(port);
  servaddr.sin_addr.s_addr=INADDR_ANY;
  bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
  listen(sockfd,3);
  clisock=accept(sockfd,NULL,NULL);
  read(clisock,&n1,sizeof(n1));
  
  memset(value,'\0',sizeof(value));
  
  for(int i=0;i<5;i++){
    if(n1==keyValue[i].key){
    sprintf(value,"the value for the %d is %s",n1,keyValue[i].val);
    break;
    }
  }
  
  if(strlen(value)==0){
    sprintf(value,"the value for the %d is not found\n",n1);
  }
  write(clisock,value,strlen(value)+1);
  printf("%s\n",value);
  
  close(clisock);
  close(sockfd);
}
