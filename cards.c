#include "cards.h"

int randInt(int max) {
    int fd = open("/dev/urandom", O_RDONLY);
    int buffer;
    
    read(fd, &buffer, 4);
    close(fd);
    
    return (unsigned int)(buffer) % max;
}

char * getWhiteCard() {
    int randIndex = randInt(1590);
    FILE *file = fopen("white.txt", "r");
    int ctr = 0;

    if (file != NULL) {
        //biggest line i've seen is like 110
        char line[256];
        while (fgets(line, sizeof line, file) != NULL) {
            if (ctr == randIndex) {
                char * retP = malloc(256);
                strcpy(retP, line);
                return retP;
            }
            else {
                ctr++;
            }
        }
        fclose(file);
    }
    return NULL;
}

char * getBlackCard() {
    int randIndex = randInt(426);
    FILE *file = fopen("black.txt", "r");
    int ctr = 0;

    if (file != NULL) {
        //biggest line i've seen is like 110
        char line[256];
        while (fgets(line, sizeof line, file) != NULL) {
            if (ctr == randIndex) {
                char * retP = malloc(256);
                strcpy(retP, line);
                return retP;
            }
            else {
                ctr++;
            }
        }
        fclose(file);
    }
    return NULL;
}

void printCard(char * toPrint) {
    //we are replacing these with their respective term versions
    const char italic[3] = "<i>";
    const char italicClose[4] = "</i>";
    const char newline[4] = "<br>";

    //so we don't modify original pointer
    char * toPrintLocal = "";
    
    //parsing
    if (strstr(toPrint, "<") == strstr(toPrint, "<i>")) {
        strncpy(toPrintLocal, toPrint, strstr(toPrint, "<") - toPrint);
        strcpy(toPrintLocal, "\e[3m");
        sprintf(toPrintLocal, "%.*s", 4, strstr(toPrint, "<") + 3);
        //debuggin
        printf("%.*s", 4, strstr(toPrint, "<") + 3);
        printf("%s", toPrintLocal);
        printCard(toPrintLocal);
    }
    else if (strstr(toPrint, "<") == strstr(toPrint, newline)) {
        
    }
    else if (strstr(toPrint, "<") == strstr(toPrint, italicClose)) {
        
    }
    else {
        printf("%s", toPrint);
    }
}

int main() {
    printf("white: %s\n", getWhiteCard());
    printf("black: %s\n", getBlackCard());
    return 0;
    printCard("ayy<i>ayy");
}
