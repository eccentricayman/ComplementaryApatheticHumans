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
//gets a white card from an index
char * getWhiteCard(int index);

//hardcoded limit: 1589 white cards
//gets a black card from an index
char * getBlackCard(int index);

//count how many times tofind occurs in string
int countOccurences(char * string, char * toFind);

//replace first instance of a string with another
char * replace(char * str , char * toReplace, char * replacingWith);

//replaces all instances of a string with another
char * replaceAll(char * str, char * toReplace, char * replacingWith);

//prints a card, with newlines, italics, and other formatting
void printCard(char * card);

//combines a black card and white card, or black card and 2 white cards
//in the first place, the second white card doesn't matter
char * combineCards(char * black, char * white1, char * white2);
