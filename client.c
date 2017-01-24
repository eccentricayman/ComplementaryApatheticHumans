#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
  
int main() {

  int sd;
  struct sockaddr_in sock;
  char buffer[1000];
  
  sd = socket(AF_INET, SOCK_STREAM, 0);   
  
  sock.sin_family = AF_INET;  
  sock.sin_addr.s_addr = INADDR_ANY;
  sock.sin_port = htons(9001);
  
  connect(sd, (struct sockaddr *)&sock, sizeof(sock));  
  
  printf("Connected to the server...\n");
  
  while(1) {

    printf("Enter your message: ");
    fgets(buffer, sizeof(buffer), stdin);
    write(sd, buffer, sizeof(buffer));

    read(sd, buffer, sizeof(buffer));
    
    printf("Received: %s\n", buffer);
  }
 
  return 0;    
}
