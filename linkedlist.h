/*
* Linked List header: Object header file for use with HW6
* Author: Cory Davis
* Version: 5/21/17
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WORD_LEN 31

typedef struct node_def {
    char word[WORD_LEN];
    int rbCount;
    int lrCount;
    struct node_def *next; 
} Node, List;

/*********************************************************************
*Creates a pointer to a null list.
*
*@params:
* -**in: A pointer to the head of an empty list.
*********************************************************************/
void *createList(List **in);

/*********************************************************************
*Inserts the given node at the front of the linked list.
*
*@params:
* -**head: The address of the first node in the linked list.
* -*new: The given node to be inserted at the front of the list.
*********************************************************************/
void insertFirst(List **, Node *);

/*********************************************************************
*Accepts a string and either creates a new node in the linked list, or
*increments the number of times it has been previously encountered.
*
*@params:
* -**head: The address of the first node in the linked list.
* -fromLR: A flag indicating which text document the data was collected
*          from.
* -*word: The string to insert into the linked list.
* -*compare: A pointer to the specified comparator function. 
*********************************************************************/
void insert(List **, int, char *, int (*compare) (const void *in1, const void *in2));

/*********************************************************************
*Frees the data allocated to each node in the given linked list.
*
*@params:
* -**head: The address of the first node in the linked list.
*********************************************************************/
void freeList(List **);

#endif