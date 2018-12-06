#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
 
#define BUFLEN 512  //Max length of buffer
#define PORT 5555   //The port on which to listen for incoming data

int main(void)
{
   struct sockaddr_in serv_addr, other_addr;
   socklen_t addr_len = sizeof (other_addr);
   int s, recv_len;
   char buf[BUFLEN];
     
   //create a UDP socket
   s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   if (s == -1)
   {
      perror("socket");
      exit(1);
   }
     
   // zero out the structure
   memset((char *) &serv_addr, 0, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(PORT);
   serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
     
   //bind socket to port
   if( bind(s, (struct sockaddr*)&serv_addr, sizeof(serv_addr) ) == -1)
   {
      perror("bind");
      exit(1);
   }
     
   //keep listening for data
   while(1)
   {
      printf("\nWaiting for data...");
      fflush(stdout);

      memset(buf,'\0', BUFLEN);
      //try to receive some data, this is a blocking call
      if ((recv_len = recvfrom(s, &buf, sizeof(buf), 0, (struct sockaddr *) &other_addr, &addr_len)) == -1)
      {
         perror("recvfrom");
         exit(1);
      }
         
      //print details of the client/peer and the data received
      printf("\nReceived message from %s:%d\n", inet_ntoa(other_addr.sin_addr), ntohs(other_addr.sin_port));
      buf[recv_len]='\0';
      printf("\nMessage received: %s", buf);
   }
   close(s);
   return 0;
}

