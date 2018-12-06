#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
 
#define SERVER "127.0.0.1"
#define BUFLEN 512  //Max length of buffer
#define PORT 5555   //The port on which to listen for incoming data

int main(void)
{
   struct sockaddr_in serv_addr;
   socklen_t addr_len = sizeof(serv_addr);
   int s; 
   char message[BUFLEN];
    
   if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
   {
      perror("socket");
      exit(1);
   }
 
   memset((char *) &serv_addr, 0, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(PORT);
     
   if (inet_aton(SERVER, &serv_addr.sin_addr) == 0) 
   {
       fprintf(stderr, "inet_aton() failed\n");
       exit(1);
   }
 
   while(1)
   {
      printf("Enter message : ");
      fgets(message, BUFLEN, stdin);

      //send the message
      if (sendto(s, &message, sizeof(message) , 0 , (struct sockaddr *) &serv_addr, addr_len)==-1)
      {
         perror("sendto");
         exit(1);
      }
         
   }
   close(s);
   return 0;
}

