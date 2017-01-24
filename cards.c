#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

//intitialize them to 1, change em to 0 once used
int usedBlackCards[425] = { 1 };
int usedWhiteCards[1589] = { 1 };

int randInt(int max) {
    int fd = open("/dev/urandom", O_RDONLY);
    int buffer;
    
    read(fd, &buffer, 4);
    close(fd);
    
    return (unsigned int)(buffer) % max;
}

char * getWhiteCard(int index) {
    FILE *file = fopen("white.txt", "r");
    int ctr = 0;

    if (file != NULL) {
        //biggest line i've seen is like 110
        char line[256];
        while (fgets(line, sizeof line, file) != NULL) {
            if (ctr == index) {
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

char * getBlackCard(int index) {
    FILE *file = fopen("black.txt", "r");
    int ctr = 0;

    if (file != NULL) {
        //biggest line i've seen is like 110
        char line[256];
        while (fgets(line, sizeof line, file) != NULL) {
            if (ctr == index) {
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

int countOccurences(char * string, char * toFind) {
    int ctr = 0;
    char * temp = string;
    while((temp = strstr(temp, toFind))) {
        ctr++;
        temp++;
    }
    return ctr;
}

char * replace(char *str, char *toReplace, char * replacingWith) {
  static char buffer[4096];
  char *p;

  if(!(p = strstr(str, toReplace))) {
      return str;
  }
  strncpy(buffer, str, p-str);
  buffer[p-str] = '\0';

  sprintf(buffer+(p-str), "%s%s", replacingWith, p+strlen(toReplace));

  return buffer;
}

char * replaceAll(char * str, char * toReplace, char * replacingWith) {
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
    localCard = replaceAll(localCard, "<i>", "\e[3m");
    //replace for </i>
    localCard = replaceAll(localCard, "</i>", "\e[0m");
    //replace <br>
    localCard = replaceAll(localCard, "<br>", "\n");
    //print
    printf("%s", localCard);
    free(localCard);
}

char * combineCards(char * black, char * white1, char * white2) {
    char * retP = malloc(strlen(black) + strlen(white1) + strlen(white2) + 1);
    retP = black;

    //coloring card1
    char * w1Local = malloc(strlen(white1) + 10);
    strcat(w1Local, "\e[34m");
    strcat(w1Local, white1);
    strcat(w1Local, "\e[0m");
    
    //coloring card2
    char * w2Local = malloc(strlen(white2) + 10);
    strcat(w2Local, "\e[34m");
    strcat(w2Local, white2);
    strcat(w2Local, "\e[0m");
    
    //check if 1 card to replace or two
    int count = countOccurences(black, "_");
    if (count == 1) {
        w1Local = replaceAll(w1Local, ".", "\0");
        char * index = strrchr(w1Local, '\n');
        w1Local[index - w1Local] = '\e';
        
        retP = replaceAll(retP, "_", w1Local);
    }
    else if (count == 2) {
        w1Local = replaceAll(w1Local, ".", "\0");
        char * index = strrchr(w1Local, '\n');
        w1Local[index - w1Local] = '\e';
        w2Local = replaceAll(w2Local, ".", "\0");
        char * index2 = strrchr(w2Local, '\n');
        w2Local[index2 - w2Local] = '\e';
        
        retP = replaceAll(retP, "_", w2Local);
        retP = replace(retP, w2Local, w1Local);
    }
    else {
        //when there's no prompt
        strcat(retP, w1Local);
    }
    //freeing colored local copies
    free(w1Local);
    free(w2Local);
    return retP;
}
