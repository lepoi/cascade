#include <stdio.h>
#include <stdlib.h>

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "auth.c"

// mostly authorization stuff
char dopreprocessing(char *client_addr, char *buffer) {
   char operation = buffer[0], *body = &buffer[2], error;

   // if (strcmp(client_addr, "127.0.0.1") != 0)
   //    return 1;

   // is it a broadcast attempt?
   if (operation == 'B') {

      goto SUCCESS;
   }

   // is it a login attempt?
   // check if username and password match
   if (operation == 'I') {
      if (error = login(body, client_addr))
         return error;
   }
   
   // is it a logout attempt?
   // look for a session and end it
   if (operation == 'O')
      return logout(client_addr);
   
   // is it a login attempt using session?
   // check if username and client_addr match
   if (operation == 'S') {
      return login_session(body, client_addr);
   }
   
   // is it a registration attempt?
   // if user doesn't exist, create record
   //    TODO: store username
   //    TODO: store password
   // register_user(client_addr);
   if (operation == 'R') {
      if (signup(body))
         return 1;      
   }

   SUCCESS:

   return 0;
}

void doprocessing(int sock, char *client_addr) {
   int n, error;
   char buffer[256];
   bzero(buffer, 256);
   n = read(sock, buffer, 255);
   
   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }

   if (error = dopreprocessing(client_addr, buffer)) {
      printf("[ %s ] [ %s ] error: %u", buffer[0], client_addr, error);
      exit(1);
   }
   
   printf("Message received: %s", buffer);

   n = write(sock, "Echo: ", 6);
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
	
   n = write(sock, buffer, sizeof(buffer) - 1);
   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
}

int main(int argc, char *argv[]) {
   int sockfd, newsockfd, portno, clilen;
   char buffer[256], client_addr[INET_ADDRSTRLEN];
   struct sockaddr_in serv_addr, cli_addr;
   int n, pid;
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }

   int true = 1;
   setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &true, sizeof(int));
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 5001;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
   
   /* Now start listening for the clients, here
      * process will go in sleep mode and will wait
      * for the incoming connection
   */
   
   listen(sockfd,5);
   clilen = sizeof(cli_addr);
   
   while (1) {
      newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		
      if (newsockfd < 0) {
         perror("ERROR on accept");
         exit(1);
      }

      // isolate client's ip address
      strcpy(inet_ntoa(cli_addr.sin_addr), client_addr);
      
      /* Create child process */
      pid = fork();
		
      if (pid < 0) {
         perror("ERROR on fork");
         exit(1);
      }
      
      if (pid == 0) {
         /* This is the client process */
         close(sockfd);
         doprocessing(newsockfd, client_addr);
         exit(0);
      }
      else {
         close(newsockfd);
      }
		
   } /* end of while */
}

