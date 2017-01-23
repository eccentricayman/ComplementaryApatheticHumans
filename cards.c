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

int countOccurences(char * string) {
    int ctr = 0;
    char * temp = string;
    while((temp = strstr(temp, "<i>"))) {
        ctr++;
        temp++;
    }
    return ctr;
}

char * replace(char * str, char * toReplace, char * replacingWith) {
    char *result; //retstr
    char *ins; //next insert point
    char *tmp;    
    int len_rep; // len of str to remove
    int len_with; // len of str to replace with
    int len_front; // distance between str to rm and last str to rm
    int count; //# of replacements

    if (!str || !toReplace)
        return NULL;
    len_rep = strlen(toReplace);
    if (len_rep == 0)
        return NULL;
    if (!replacingWith)
        replacingWith = "";
    len_with = strlen(replacingWith);

    // count the number of replacements needed
    ins = str;
    for (count = 0; (tmp = strstr(ins, toReplace)); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(str) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in str
    //    str points to the remainder of str after "end of rep"
    while (count--) {
        ins = strstr(str, toReplace);
        len_front = ins - str;
        tmp = strncpy(tmp, str, len_front) + len_front;
        tmp = strcpy(tmp, replacingWith) + len_with;
        str += len_front + len_rep;
    }
    strcpy(tmp, str);
    return result;
}

void printCard(char * card) {
    //local copy
    char *localCard = malloc (strlen (card) * 2);
    localCard = card;
    //replace for <i>
    localCard = replace(localCard, "<i>", "\e[3m");
    //replace for </i>
    localCard = replace(localCard, "</i>", "\e[0m");
    //replace <br>
    localCard = replace(localCard, "<br>", "\n");
    //print
    printf("%s", localCard);
    free(localCard);
}
