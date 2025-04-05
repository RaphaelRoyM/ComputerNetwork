#include<stdio.h>
//#include<stdlib.h>
#include <unistd.h>
#include<sys/types.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>//possible server address classification stored in this
int main(void){
	int socket_desc;
	struct sockaddr_in server_addr;
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
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	server_addr.sin_port=htons(2000);
	//send connection request
	if(connect(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0){
		printf("error connecting\n");
		return -1;
	}
	printf("connected with server successfully\n");
	//get input from thr user
	printf("enter the message to send to server\t");
	fgets(client_message, sizeof(client_message), stdin);

	//send the message to server
	if(send(socket_desc,client_message,strlen(client_message),0)<0){
		printf("error sending message to server\n");
		return -1;
	}
	if(recv(socket_desc,server_message,sizeof(server_message),0)<0){
		printf("error sending message to server\n");
		return -1;
	}
	printf("server response %s",server_message);
	close(socket_desc);
	
	
}
