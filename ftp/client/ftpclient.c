// FTP CLIENT 
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
    int sockfd;
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;    // Connect to any available interface
    serv_addr.sin_port = htons(PORT);

    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    printf("Enter command: ");
    scanf("%s", command);
    printf("Enter file name: ");
    scanf("%s", fileName);

    write(sockfd, command, sizeof(command));
    write(sockfd, fileName, sizeof(fileName));

    FILE *fp;
    if (!strcmp(command, "get")) {
        fp = fopen(fileName, "w");
        read(sockfd, buffer, sizeof(buffer) - 1);
        fprintf(fp, "%s", buffer);
        fclose(fp);
    } else if (!strcmp(command, "put")) {
        fp = fopen(fileName, "r");
        if (fp) {
            fgets(buffer, sizeof(buffer), fp);
            write(sockfd, buffer, strlen(buffer));
            fclose(fp);
        } else {
            printf("File not found.\n");
        }
    } else {
        printf("Invalid command.\n");
    }

    close(sockfd);
    return 0;
}
