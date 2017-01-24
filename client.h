#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "cards.h"

//is the user the czar?
int czar;

//index of this user's cards
int * cards;

//connects to the server
int client_connect(char *host);

//prints user cards
void printCards();
