#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>

//is the user the czar?
int czar;

//index of this user's cards
int * cards;

//connects to the server
int client_connect(char *host);

//prints user cards

