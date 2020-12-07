#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char *argv[]){

int PORT;
int opt;

   if(argc >= 2) {

     while((opt = getopt(argc, argv, "p:")) != -1) {
          
     switch(opt) {
     case 'p': PORT = atoi(optarg); 
         break;
     default: printf("You have to specify PORT number!"); 
         return -1;
      }
    }
   } else {
        printf("You have to specify PORT number!");
        return -1;
}

   struct sockaddr_in server;

   int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

   server.sin_family = AF_INET;
   server.sin_port = htons(PORT);
   server.sin_addr.s_addr = inet_addr("127.0.0.1");

   if (connect(socket_fd, (struct sockaddr*) &server, sizeof(server)) < 0) {
     printf("Could not connect to server\n");
     return -1;
  }

   char server_msg[2000];
   memset(server_msg, '\0', sizeof(server_msg));

   if (recv(socket_fd, server_msg, sizeof(server_msg), 0) < 0) {
     printf("Didn't receive handshake from server!\n");
     return -1;
  }

   char reply;
   printf("Server ID: %s, is trying to connect. Accept? [Y/n]\n", server_msg);
   reply = getchar();
   getchar();

   if (tolower(reply) != 'y') {
     printf("Client declined!\n");
     return -1;
  }

   while(1) {
      char client_msg[2000];
      memset(client_msg, '\0', sizeof(client_msg));

      printf("Send message to server: ");
      fgets(client_msg,400,stdin);

      send(socket_fd, client_msg, strlen(client_msg), 0);
   }
}
