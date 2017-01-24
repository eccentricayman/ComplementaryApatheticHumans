#include "game.h"

int server_setup() {

  int sd, i;

  sd = socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_addr.s_addr = INADDR_ANY;
  sock.sin_port = htons(9001);
  
  i = bind(sd, (struct sockaddr *)&sock, sizeof(sock));
  
  return sd;
}

int server_connect(int sd) {
 
  int connection, i;

  i = listen(sd, 4);
  
  struct sockaddr_in sock1;
  unsigned int sock1_len = sizeof(sock1);
  connection = accept(sd, (struct sockaddr *)&sock1, &sock1_len);

  printf("[GAME] CONNECTED TO %s\n", inet_ntoa(sock1.sin_addr));

  return connection;
}

int main() {

  int sd, connection;

  sd = server_setup();
  char buffer[1000];
  connection = server_connect(sd);
 
  while (read( connection, buffer, sizeof(buffer) ))
    printf("[SERVER %d] received: %s\n", getpid(), buffer );

  close(connection);
  
  return 0;
}
