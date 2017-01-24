#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

<<<<<<< HEAD:join.h
//is the user the czar?
int czar;

//index of this user's cards
int * cards;

//connects to the server
int client_connect(char *host);

//prints user cards

=======
int client_connect(char * host);
>>>>>>> b3f2703e56eac99a9495f94a44cc7fe2389177a4:client.h
