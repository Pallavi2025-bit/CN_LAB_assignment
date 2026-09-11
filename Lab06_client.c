#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define SIZE 4096

int main()
{
    int sock_fd;
    struct sockaddr_in server_addr;

    FILE *fp;

    char id[20];
    char file_data[SIZE];
    char send_data[SIZE];
    char response[SIZE];

    fp = fopen("data.txt", "r");

    if (fp == NULL)
    {
        printf("data.txt not found\n");
        return 1;
    }

    memset(file_data, 0, SIZE);

    fread(file_data, 1, SIZE - 1, fp);

    fclose(fp);

    printf("Enter Student ID to search: ");
    scanf("%s", id);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    inet_pton(AF_INET, "127.0.0.1",
              &server_addr.sin_addr);

    connect(sock_fd,
            (struct sockaddr *)&server_addr,
            sizeof(server_addr));

    sprintf(send_data, "%s\n%s", id, file_data);

    write(sock_fd, send_data, strlen(send_data));

    memset(response, 0, SIZE);

    read(sock_fd, response, SIZE - 1);

    printf("Server Response: %s\n", response);

    close(sock_fd);

    return 0;
}
