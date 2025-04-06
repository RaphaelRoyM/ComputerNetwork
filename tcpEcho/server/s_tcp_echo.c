#include<stdio.h>
//#include<stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>//possible server address classification stored in this
int main(void){
  int socket_desc,client_sock,client_size;
  struct sockaddr_in server_addr,client_addr;
  char server_message[2000],client_message[2000];
  
  //clean buffers
  memset(server_message,'\0', sizeof(server_message));
  memset(client_message,'\0', sizeof(client_message));
  //create socket
  socket_desc=socket(AF_INET,SOCK_STREAM,0);
  if (socket_desc<0){
    printf("error while creating socket\n");
    return -1;
  }
  printf("socket created\n");
  //set port and IP
  server_addr.sin_family=AF_INET;
  server_addr.sin_addr.s_addr=INADDR_ANY;
  server_addr.sin_port=htons(2000);
  
  if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
    printf("binding error\n");
    return -1;
  }
  printf("binding succesful\n");
  //listening for any client connection
  if(listen(socket_desc,1)<0){
    printf("error listening\n");
    return -1;
  }
  printf("listening on the port\n");
  client_size = sizeof(client_addr);
client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, (socklen_t*)&client_size);

  if(client_sock<0){
    printf("client socket error\n");
    return -1;
  }
  printf("client socket accepted at the IP : %s \nand port : %i\n",inet_ntoa(client_addr.sin_addr),htons(client_addr.sin_port));
  //receive client's message:
  if(recv(client_sock,client_message,sizeof(client_message),0)<0){
    printf("receive error\n");
    return -1;
  }
  printf("the message from client is %s\n",client_message);
  //response
  strcpy(server_message,"this is server message.we recieved your message.\n");
  if((send(client_sock,server_message,strlen(server_message),0))<0){
    printf("send failed\n");
    return -1;
  }
  //close
  close(client_sock);
  close(socket_desc);
}
