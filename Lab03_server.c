#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

//Server code
#define PORT 8081
#define BUFFER_SIZE 1024

int main(){
      int server_fd, new_socket;
      struct sockaddr_in address;
      int addrlen = sizeof(address);

      char buffer[BUFFER_SIZE];
      char message[BUFFER_SIZE];

      //Socket creation
      server_fd = socket(AF_INET, SOCK_STREAM, 0);
      if (server_fd <0){
             perror("Socket creation failed");
            exit(1);
      }
     //configure address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    //Bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
            perror("Bind failed");
exit(1);
    }
   //listen for connections
   if (listen (server_fd,5)<0) {
       perror ("listen failed");
       exit(1);
   }
   printf("Server listening on the port %d  \n", PORT);

 // Accept connection

  new_socket = accept(server_fd, (struct sockaddr *)& address, (socklen_t *) & addrlen);

   if(new_socket<0){
    perror("Accept failed");
    exit(1);
  }

  printf("client communicated \n");

//communication loop

   while(1){
        read(new_socket,buffer,1024);
        printf("client:%s",buffer);
        if(strcmp(buffer,"bye\n") ==0){
            break;
        }
        printf("server:");
fgets(message,sizeof(message),stdin);
        send(new_socket,message,strlen(message),0);
        if(strcmp(buffer,"bye\n") ==0){
            break;
        }
       }

   close(new_socket);
   close(server_fd);
    return 0;
}
