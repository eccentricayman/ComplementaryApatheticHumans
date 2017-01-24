#include "server.h"

int server_setup() {

  int sd;

  sd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in sock;
  sock.sin_family = AF_INET;
  sock.sin_addr.s_addr = INADDR_ANY;
  sock.sin_port = htons(9001);

  bind(sd, (struct sockaddr *)&sock, sizeof(sock));

  return sd;
}

int main() {
  
  int sd, connection, len, i;
  struct sockaddr_in sock, sock1;
  char buffer[1000], client[100];
  pid_t childpid;
  char * players[4];

  sd = server_setup();

  for (i = 0; i < 4; i++)
    players[i] = 0;

  printf("Waiting for a connection...\n");
  
  listen(sd, 4);

  i = 0;

  while (1) {

    len = sizeof(sock1);
    
    connection = accept(sd, (struct sockaddr *)&sock1, &len);
    
    if (players[3] == 0) {
      
      read(connection, buffer, sizeof(buffer));
      strcpy(client, buffer);
      players[i] = (char *)malloc(strlen(buffer)+1);
      strcpy(players[i], buffer);
      i++;
      
      printf("Connection accepted...\n");
      
      int a;
      for (a = 0; a < 4; a++)
	printf("Player %d: %s\n", a, players[a]);
      
      if ((childpid = fork()) == 0) {

	close(sd);
	
	while (1) {

	  read(connection, buffer, sizeof(buffer));
	  printf("Received data from %s: %s\n", client, buffer);

	  write(connection, buffer, sizeof(buffer));
	  printf("Sent data to %s: %s\n", client, buffer);
	}
      }
    
      close(connection);
    }
  }

  return 0;
}
