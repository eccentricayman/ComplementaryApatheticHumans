#include "cards.h"
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
    //keep track of czar server-side
    int czar = 0;

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
                    //to store cards
                    char answers[4][1000];
                    
                    //get a black card
                    char * black = getBlackCard(randInt(425));
                    printf("Black Card: %s\n", black);
                    write(connection, black, sizeof(black));
                    
                    read(connection, buffer, sizeof(buffer));
                    printf("Received data from %s: %s\n", client, buffer);
                    for (int i = 0 ; i < 4 ; i++) {
                        if (!strcmp(client, players[i])) {
                            strcpy(answers[i], buffer);
                        }
                    }
                    //send data to czar
                    if (!strcmp(client, players[czar])) {
                        strcpy(buffer, combineCards(black, answers[i], NULL));
                        write(connection, buffer, sizeof(buffer));
                        printf("Sent data to %s: %s\n", client, buffer);
                        //read from czar
                        read(connection, buffer, sizeof(buffer));
                        for (int i = 0 ; i < 4 ; i++) {
                            if (!strcmp(answers[i], buffer)) {
                                czar = i;
                            }
                        }
                    }
                    //new czar
                    if (!strcmp(client, players[czar])) {
                        
                    }
                    else {
                        int rand = randInt(1590);
                        write(connection, &rand, sizeof(rand));
                    }
                }
            }
    
            close(connection);
        }
    }

    return 0;
}
