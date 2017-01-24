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

void printCards() {
    int ctr = 1;
    int * cardsLocal = cards;
    if (cards) {
        printf("Your Cards:\n");
        while (cardsLocal) {
            printf("%d.", ctr);
            printCard(getWhiteCard(*cardsLocal));
            cardsLocal++;
            ctr++;
        }
    }
}

int main() {

    int sd;
    char blackCard[1000];
    char cardChoiceInput[10];
    int cardChoice;
    char buffer[1000];
    char * host = "127.0.0.1";

    sd = client_connect(host);

    printf("What will your display name be? ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(buffer, '\n') = 0;
    write(sd, buffer, sizeof(buffer));

    while(1) {
        if (czar) {
            printf("\e[0;31mYou are the czar this turn!\e[0m");
        }
        else {
            printCards();
            //read and print black card from server
            read(sd, blackCard, sizeof(blackCard));
            printf("\e[0;32m");
            printCard(blackCard);
            printf("\e[0m\n");

            //get card
            printf("Pick a Card: ");
            fgets(cardChoiceInput, 10, stdin);
            cardChoice = atoi(cardChoiceInput);
            //write that white card to buffer
            strcpy(buffer, getWhiteCard(cardChoice));
            write(sd, buffer, sizeof(buffer));
            
            read(sd, buffer, sizeof(buffer));
            
            printf("Received: %s\n", buffer);
        }
    }

    return 0;
}
