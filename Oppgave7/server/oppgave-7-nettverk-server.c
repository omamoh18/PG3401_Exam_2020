#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){

int PORT;
char *ID;
int opt;

   if (argc >= 2) {

   while ((opt = getopt(argc, argv, "p:i:")) != -1) {

     switch(opt){
     case 'p': PORT = atoi(optarg); 
         break;
     case 'i': ID = optarg; 
         break;
     default: printf("You have to specify PORT and ID arguments!\n"); 
         return -1;
        }
     }
   } else {
     printf("You have to specify PORT and ID arguments!\n");
     return -1;
   }

   printf("PORT %d and ID %s\n", PORT, ID);

   struct sockaddr_in server_addr, client_addr;

   int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

   memset(&server_addr, 0, sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_addr.s_addr = INADDR_ANY;
   server_addr.sin_port = htons(PORT);

   if (bind(socket_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)) < 0) {
     printf("Socket binding failed!\n");
     return -1;
   }
   printf("Binding complete!\n");

   printf("Listening...\n");

   if (listen(socket_fd, 5) < 0) {
      printf("Listen failed!\n");
      return -1;
   }

   while(1){
      char client_msg[2000];
      int client_size = sizeof(client_addr);
      int new_socket = accept(socket_fd, (struct sockaddr*) &client_addr, &client_size);

      char handshake_msg[2000];
      strcpy(handshake_msg, ID);

      if(send(new_socket, handshake_msg, strlen(handshake_msg), 0) < 0) {
        printf("Couldn't send message\n");
        return -1;
      }

      while(recv(new_socket , client_msg, sizeof(client_msg), 0) != 0){
      //printf("Couldn't receive\n");
         printf("Message from client: %s\n", client_msg);
     }
     //printf("Message from client: %s\n", client_msg);
   }
}
