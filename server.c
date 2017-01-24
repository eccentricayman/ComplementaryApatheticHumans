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

int server_connect(int master_socket) {
  
    int connection, new_socket, client_socket[4], max_clients, sd, max_sd, i;
    max_clients = 4;
  
    fd_set readfds;
  
    struct sockaddr_in sock;
    unsigned int sock_len = sizeof(sock);
  
    for (i = 0; i < max_clients; i++)
        client_socket[i] = 0;
  
    printf("Waiting for connections on port %d\n", 9001);
  
    listen(sd, 4);
  
    while (client_socket[3] == 0) {
        FD_ZERO(&readfds);

        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        for (i = 0 ; i < max_clients ; i++) {  
 
            sd = client_socket[i];  

            if (sd > 0)
                FD_SET(sd, &readfds);
                
            if(sd > max_sd)  
                max_sd = sd;
        }
    
        select(max_sd + 1, &readfds, NULL, NULL, NULL);
    
        if (FD_ISSET(master_socket, &readfds)) {
            new_socket = accept(master_socket, (struct sockaddr *)&sock, &sock_len);
      
            printf("New connection, socket fd: %d, ip: %s, port: %d\n",
                   new_socket, inet_ntoa(sock.sin_addr), ntohs(sock.sin_port));
      
            for (i = 0; i < max_clients; i++) {  
                if(client_socket[i] == 0) {  
                    client_socket[i] = new_socket;  
                    printf("Adding to list of sockets as %d\n" , i);  
	  
                    break;  
                }
            }
        }
    }
    return 1; //WHAT DO I RETURN HERE?????
}

int main()  {

    int master_socket, connection;
  
    master_socket = server_setup();
    char buffer[1000];
  
    return 0;  
}  
