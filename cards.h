#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

//intitialize them to 1, change em to 0 once used
int usedBlackCards[425] = { 1 };
int usedWhiteCards[1589] = { 1 };

//random int from [0, max)
int randInt(int max);

//hardcoded limit: 425 black cards
//Returns random white card as a string and removes it from cards
char * getWhiteCard();

//hardcoded limit: 1589 white cards
//Returns random black card as a string and removes it from cards
char * getBlackCard();

//replaces part of a string with another
char * replace(char * str, char * toReplace, char * replacingWith);

//prints a card, with newlines, italics, and other formatting
void printCard(char * card);
