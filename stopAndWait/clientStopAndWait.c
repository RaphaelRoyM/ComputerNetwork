#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>  // Added to define errno, EAGAIN, and EWOULDBLOCK

#define PORT 8080
#define BUFFER_SIZE 255

int main(int argc, char *argv[]) {
    int sock_fd, total_frames, next_frame = 0;
    struct sockaddr_in serv_addr;
    socklen_t serv_len = sizeof(serv_addr);

    // Check command-line arguments
    if (argc != 2) {
        printf("Usage: %s <total_frames>\n", argv[0]);
        exit(1);
    }
    total_frames = atoi(argv[1]);

    // Create socket
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Set timeout using setsockopt
    struct timeval tv;
    tv.tv_sec = 2;  // 2 seconds timeout
    tv.tv_usec = 0;
    if (setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
        perror("Error setting timeout");
        close(sock_fd);
        exit(1);
    }

    // Set up server address
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP (localhost)
    serv_addr.sin_port = htons(PORT);

    printf("Client started. Sending %d frames...\n", total_frames);

    while (next_frame < total_frames) {
        // Send frame
        printf("Sending frame: %d\n", next_frame);
        ssize_t n = sendto(sock_fd, &next_frame, sizeof(next_frame), 0, (struct sockaddr *)&serv_addr, serv_len);
        if (n < 0) {
            perror("Error sending frame");
            break;
        }

        // Receive ACK
        int ack_frame;
        n = recvfrom(sock_fd, &ack_frame, sizeof(ack_frame), 0, (struct sockaddr *)&serv_addr, &serv_len);
        if (n < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                printf("Timeout occurred for frame %d, resending...\n", next_frame);
                continue; // Resend the same frame
            } else {
                perror("Error receiving ACK");
                break;
            }
        }

        // Process ACK
        if (ack_frame == -1) {
            printf("Received NAK for frame %d, resending...\n", next_frame);
            continue; // Resend the same frame
        } else if (ack_frame == next_frame + 1) {
            printf("Received ACK: %d\n", ack_frame);
            next_frame++; // Move to next frame
        }
    }

    close(sock_fd);
    printf("Client stopped.\n");
    return 0;
}
