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
  
  if(bind(sock_desc,(struct sockaddr*)&servaddr,sizeof(servaddr))<0){
    printf("bind error\n");
    return -1;
  }
  if(listen(sock_desc,1)<0){
    printf("listen error\n");
    return -1;
  }
  int client_sock=accept(sock_desc,NULL,NULL);
  if(client_sock<0){
    printf("accept error\n");
    return -1;
  }
  char buffer[256],temp;
  bzero(buffer,256);
  int rd=read(client_sock,buffer,sizeof(buffer));
  for(int i=0;i<strlen(buffer)/2;i++){
    temp=buffer[i];
    buffer[i]=buffer[(strlen(buffer)-i-1)];
    buffer[(strlen(buffer)-i-1)]=temp;
  }
  printf("reversed string is : %s",buffer);
  int wr=write(client_sock,buffer,strlen(buffer));
  
  close(sock_desc);
  
}
