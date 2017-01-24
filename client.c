#include "client.h"

int client_connect(char * host) {

  int sd;
  struct sockaddr_in sock;

  sd = socket(AF_INET, SOCK_STREAM, 0);

  sock.sin_family = AF_INET;
  inet_aton(host, &(sock.sin_addr));
  sock.sin_port = htons(9001);

  connect(sd, (struct sockaddr *)&sock, sizeof(sock));

  printf("Connected to the server...\n");
  
  return sd;
}

int main() {

  int sd;
  char buffer[1000];
  char * host = "127.0.0.1";

  sd = client_connect(host);
  
  printf("What will your display name be? ");
  fgets(buffer, sizeof(buffer), stdin);
  *strchr(buffer, '\n') = 0;
  write(sd, buffer, sizeof(buffer));
  
  while(1) {
    
    printf("Enter your message: ");
    fgets(buffer, sizeof(buffer), stdin);
    write(sd, buffer, sizeof(buffer));
    
    read(sd, buffer, sizeof(buffer));
    
    printf("Received: %s\n", buffer);
  }

  return 0;
}
