#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER_SIZE 1024

//CLIENT CODE
 int main(){
    int sock;
    struct sockaddr_in serv_addr;

    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];
    // SOCKET creation
   sock = socket(AF_INET, SOCK_STREAM,0);

   if (sock<0){
     perror("socket creation failed");
     exit(1);
   }

//configure server address
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(PORT);
   inet_pton(AF_INET, "127.0.0.1",&serv_addr.sin_addr);
//connect to server
  if (connect(sock,(struct sockaddr *)& serv_addr,sizeof(serv_addr))<0){
      perror("connection failed");
exit(1);
   }

  printf("connected to server");
//loop

   while(1){
       printf("client:");
       fgets(message, sizeof(message),stdin);
       send(sock, message,strlen(message),0);
        if(strcmp(buffer,"bye\n") ==0){
            break;
        }
       read(sock,buffer,1024);
       printf("Server:%s",buffer);
       if(strcmp(buffer,"bye\n") ==0){
            break;
        }
   }
   close(sock);
   return 0;
}
