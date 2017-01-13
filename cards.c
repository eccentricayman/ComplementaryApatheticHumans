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
    
}

char * getBlackCard() {
    int randIndex = randInt(426);
    
}
