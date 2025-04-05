//FTP Server

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9001
#define BUFFER_SIZE 1024

int main() {
    char command[10] = {0}, fileName[10] = {0}, buffer[BUFFER_SIZE] = {0};
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;   // Accept connections from any IP
    serv_addr.sin_port = htons(PORT);

    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(sockfd, 5);

    printf("Waiting for connection...\n");
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

    read(newsockfd, command, sizeof(command));
    read(newsockfd, fileName, sizeof(fileName));

    FILE *fp;
    if (!strcmp(command, "get")) {
        fp = fopen(fileName, "r");
        if (fp) {
            fread(buffer, 1, sizeof(buffer), fp);
            write(newsockfd, buffer, strlen(buffer));
            fclose(fp);
        } else {
            write(newsockfd, "File not found", 14);
        }
    } else if (!strcmp(command, "put")) {
        fp = fopen(fileName, "w");
        read(newsockfd, buffer, sizeof(buffer));
        fprintf(fp, "%s", buffer);
        fclose(fp);
    } else {
        printf("Invalid command.\n");
    }

    close(newsockfd);
    close(sockfd);
    return 0;
}
