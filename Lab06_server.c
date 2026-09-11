#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>

#define PORT 8080
#define SIZE 4096

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;
    pid_t pid;

    char buffer[SIZE];
    char response[SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server_addr,
         sizeof(server_addr));

    listen(server_fd, 5);

    printf("Server started...\n");

    signal(SIGCHLD, SIG_IGN);

    while (1)
    {
        client_len = sizeof(client_addr);

        client_fd = accept(server_fd,
                           (struct sockaddr *)&client_addr,
                           &client_len);

        pid = fork();

        if (pid == 0)
        {
            close(server_fd);

            memset(buffer, 0, SIZE);
            read(client_fd, buffer, SIZE);

            char *id = strtok(buffer, "\n");
            char *data = strtok(NULL, "");

            int found = 0;

            if (id != NULL && data != NULL)
            {
                char temp[SIZE];
                strcpy(temp, data);

                char *line = strtok(temp, "\n");

                while (line != NULL)
                {
                    char student_id[20];

                    sscanf(line, "%s", student_id);

                    if (strcmp(id, student_id) == 0)
                    {
                        sprintf(response, "Record Found: %s", line);
                        found = 1;
                        break;
                    }

                    line = strtok(NULL, "\n");
                }
            }

            if (found == 0)
            {
                strcpy(response, "Record Not Found");
            }

            write(client_fd, response, strlen(response));

            close(client_fd);
            exit(0);
        }

        else
        {
            close(client_fd);
        }
    }

    return 0;
}
