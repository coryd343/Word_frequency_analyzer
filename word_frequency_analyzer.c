/*
* HW 6: Using An Array Of Nested Structures
* Author: Cory Davis
* Version: 5/21/17
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "sort.h"

int sortAlph(const void *, const void *);
int sortCountDiff(const void *, const void *);
void printList(List *);
void printRange(List *head, int rngStr, int rngEnd);
void filter(char wordIn[WORD_LEN]);
int viableChar(char);
int getNumNodes(List *);
void getData(List **, FILE *, FILE *);

int main(void) {
    FILE *rb, *lr;
    if(!((rb = fopen("RedBadge.txt", "r")) && (lr = fopen("LittleRegiment.txt", "r")))) {
        printf("Error opening text files!\n");
        exit(0);
    }
    List *wordList = createList(&wordList);
    getData(&wordList, lr, rb);
    //printList(wordList);
    int numNodes = getNumNodes(wordList);
    printf("There are %d unique words!\nSorted alphabetically:\n", numNodes);
    printRange(wordList, 1, 25);
    mergeSort(&wordList, sortCountDiff);
    printf("Sorted by greatest difference:\n");
    printRange(wordList, 1, 25);
    printRange(wordList, (numNodes - 4), numNodes);
    freeList(&wordList);
    fclose(rb);
    fclose(lr);
    return 0;
}

/*********************************************************************
*Compares two strings alphabetically.
*Returns a negative number if in1 < in2,
*Returns 0 if in1 = in2,
*Returns a positive number if in1 > in2.
*This function is intended to be passed as a comparator to the linked
*list.
*
*@params:
* -*in1: The first string.
* -*in2: The second string.
*********************************************************************/
int sortAlph(const void *in1, const void *in2) {
    return strcmp((char *) in1, (char *) in2);
}

/*********************************************************************
*Compares two linked list nodes by difference in word count
*first, then by word length (if the first test returns 0), finally by
*reverse alphabetical (if the second test returns 0).
*Returns a negative number if in1 < in2,
*Returns 0 if in1 = in2,
*Returns a positive number if in1 > in2.
*This function is intended to be passed as a comparator to the linked
*list.
*
*@params:
* -*in1: The first linked list node.
* -*in2: The second linked list node.
*********************************************************************/
int sortCountDiff(const void *in1, const void *in2) {    
    int rb1 = ((Node*)in1)->rbCount, lr1 = ((Node*)in1)->lrCount,
        rb2 = ((Node*)in2)->rbCount, lr2 = ((Node*)in2)->lrCount;
    int diff1 = abs(rb1 - lr1);
    int diff2 = abs(rb2 - lr2);
    int diff = diff1 - diff2;
    if(diff) {
       return diff;
    }
    else {
        //Counts are equal
        int length = (strlen(((Node*)in1)->word) - strlen(((Node*)in2)->word));
        if(length) {
            return length;
        }
        else {
            return strcmp((((Node*)in2)->word), (((Node*)in1)->word));
        }
    }
}

/*********************************************************************
*Prints the data in all nodes of the given linked list.
*
*@params:
* -*head: The first node in the given linked list.
*********************************************************************/
void printList(List *head) {
    int count = 1;
    while(head) {
        printf("%d. %31s\tRedBadge: %4d, LittleRegiment: %4d, Difference: %4d\n", count++,
        head->word, head->rbCount, head->lrCount, abs((head->rbCount) - (head->lrCount)));
        head = head->next;
    }
    printf("\n\n");
}

/*********************************************************************
*Prints the data from the nodes in the specified range of the given
*linked list.
*
*@params:
* -*head: The first node in the given linked list.
* -rngStr: The index starting the range to be printed.
* -rngEnd: The index ending the range to be printed.
*********************************************************************/
void printRange(List *head, int rngStr, int rngEnd) {
    for(int i = 1; i < rngStr; i++) {
        head = head->next;
    }
    for(; rngStr <= rngEnd; rngStr++) {
        printf("%d. %31s\tRedBadge: %4d, LittleRegiment: %4d, Difference: %4d\n", rngStr,
        head->word, head->rbCount, head->lrCount, abs((head->rbCount) - (head->lrCount)));
        head = head->next;
    }
    printf("\n\n");
}

/*********************************************************************
*Removes the invalid characters from the given string. Until the first
*valid character is found, then returns every valid character until
*the next invalid character is detected or the end of the word is
*reached.
*
*@params:
* -wordIn: The string to be filtered.
*********************************************************************/
void filter(char wordIn[WORD_LEN]) {
    char *read = wordIn;
    int i = 0;
    while(!viableChar(*read)) {
        read++;
    }    
    while(viableChar(*read)) {
        if(*read >= 'A' && *read <= 'Z') {
           wordIn[i] = *read + ('a' - 'A');
        }
        else {
            wordIn[i] = *read;
        }
        i++;
        read++;
    }
    wordIn[i] = '\0';
}

/*********************************************************************
*Tests the given character to determine whether or not it is a letter,
*apostrophe or hyphen.
*Returns 1 if the character is valid.
*Returns 0 if the character is invalid.
*
*@params:
* -in: The character to be tested.
*********************************************************************/  
int viableChar(char in) {
    return ((in >= 'a' && in <= 'z') || (in >= 'A' && in <= 'Z') || in == '\'' || in == '-');
}

/*********************************************************************
*Tests the given string to determine whether or not it contains valid
*characters.
*Returns 1 if the string contains valid characters.
*Returns 0 if the string does not contains valid characters.
*
*@params:
* -*in: The string to be tested.
*********************************************************************/
int validWord(char *in) {
    for(int i = 0; i < strlen(in); i++) {
        if(viableChar(in[i])) {
            return 1;
        }
    }
    return 0;
}

/*********************************************************************
*Iterates through the given linked list and returns the number of
*nodes it contains.
*
*@params:
* -*head: The first node of the linked list.
*********************************************************************/
int getNumNodes(List *head) {
    int count = 0;
    while(head) {
        head = head->next;
        count++;
    }
    return count;
}

/*********************************************************************
*Reads every string token from the two given text documents, filters
*out the invalid characters and creates an alphabetized linked list.
*
*@params:
* -**head: The address of the first node in the linked list.
* -*lr: The first text document to process.
* -*rb: The second text document to process.
*********************************************************************/
void getData(List **head, FILE *lr, FILE *rb) {
    char curr[WORD_LEN];
    while(fscanf(lr, " %s", curr) != EOF) {
        if(validWord(curr)) {
            filter(curr);
            insert(head, 1, curr, sortAlph);
        }
    }
    while(fscanf(rb, " %s", curr) != EOF) {
        if(validWord(curr)) {
            filter(curr);
            insert(head, 0, curr, sortAlph);
        }
    }
}