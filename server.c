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
  
    int sd, connection, len;
    struct sockaddr_in sock, sock1;
    char buffer[1000];
    pid_t childpid;
    char client[100];

    sd = server_setup();

    printf("Waiting for a connection...\n");
  
    listen(sd, 4);

    while (1) {

        len = sizeof(sock1);
    
        connection = accept(sd, (struct sockaddr *)&sock1, &len);

        read(connection, buffer, sizeof(buffer));
        strcpy(client, buffer);

        printf("Connection accepted...\n");
    
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

    return 0;
}
