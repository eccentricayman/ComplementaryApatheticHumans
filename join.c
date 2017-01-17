#include "join.h"

int client_connect(char *host) {

  int sd, i;

  sd = socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  inet_aton(host, &(sock.sin_addr));
  sock.sin_port = htons(9001);
  
  printf("[CLIENT] JOINING GAME: %s\n" , host);
  i = connect(sd , (struct sockaddr *)&sock, sizeof(sock));
  
  return sd;
}
