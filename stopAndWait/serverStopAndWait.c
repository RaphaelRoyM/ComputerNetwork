#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 255

int main(int argc, char *argv[]) {
    int sockfd, total_frames, num_lost, num_timeout;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len = sizeof(cli_addr);

    // Check command-line arguments
    if (argc != 2) {
        printf("Usage: %s <total_frames>\n", argv[0]);
        exit(1);
    }
    total_frames = atoi(argv[1]);

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Bind socket
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(1);
    }
    printf("Server started. Listening on port %d...\n", PORT);

    // Input lost frames
    printf("Enter number of lost frames: ");
    scanf("%d", &num_lost);
    int lost_list[num_lost];
    if (num_lost > 0) {
        printf("Enter frame numbers of lost frames (0 to %d):\n", total_frames - 1);
        for (int i = 0; i < num_lost; i++) {
            scanf("%d", &lost_list[i]);
        }
    }

    // Input timeout frames
    printf("Enter number of timeout frames: ");
    scanf("%d", &num_timeout);
    int timeout_list[num_timeout];
    if (num_timeout > 0) {
        printf("Enter frame numbers of timeout frames (0 to %d):\n", total_frames - 1);
        for (int i = 0; i < num_timeout; i++) {
            scanf("%d", &timeout_list[i]);
        }
    }

    int next_frame = 0;
    while (next_frame < total_frames) {
        int recv_frame;
        ssize_t n = recvfrom(sockfd, &recv_frame, sizeof(recv_frame), 0, (struct sockaddr *)&cli_addr, &cli_len);
        if (n < 0) {
            perror("Error receiving frame");
            continue;
        }
        printf("Received frame: %d\n", recv_frame);

        // Check if frame is in lost_list
        int is_lost = 0;
        for (int i = 0; i < num_lost; i++) {
            if (recv_frame == lost_list[i]) {
                is_lost = 1;
                int nak = -1;
                sendto(sockfd, &nak, sizeof(nak), 0, (struct sockaddr *)&cli_addr, cli_len);
                printf("Sent NAK (-1) for frame %d\n", recv_frame);
                // Remove from lost_list by shifting (simulate one-time resend)
                for (int j = i; j < num_lost - 1; j++) {
                    lost_list[j] = lost_list[j + 1];
                }
                num_lost--;
                break;
            }
        }

        // Check if frame is in timeout_list (server doesn't respond, client times out)
        if (!is_lost) {
            int is_timeout = 0;
            for (int i = 0; i < num_timeout; i++) {
                if (recv_frame == timeout_list[i]) {
                    is_timeout = 1;
                    printf("Simulating timeout for frame %d (no response sent)\n", recv_frame);
                    // Remove from timeout_list (simulate one-time resend)
                    for (int j = i; j < num_timeout - 1; j++) {
                        timeout_list[j] = timeout_list[j + 1];
                    }
                    num_timeout--;
                    break;
                }
            }

            // Normal case: send ACK (next expected frame)
            if (!is_timeout) {
                next_frame = recv_frame + 1;
                sendto(sockfd, &next_frame, sizeof(next_frame), 0, (struct sockaddr *)&cli_addr, cli_len);
                printf("Sent ACK: %d\n", next_frame);
            }
        }
    }

    close(sockfd);
    printf("Server stopped.\n");
    return 0;
}
