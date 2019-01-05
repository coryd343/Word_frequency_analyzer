/*
* Linked List: Object file for use with HW6
* Author: Cory Davis
* Version: 5/21/17
*/

#include "linkedlist.h"

/*********************************************************************
*Creates a pointer to a null list.
*
*@params:
* -**in: A pointer to the head of an empty list.
*********************************************************************/
void *createList(List **in) {
    *in = NULL;
    return *in;
}

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
void insert(List **head, int fromLR, char *word, int (*compare) (const void *in1, const void *in2)) {
    //int count = 1;
    //printf("\tInsert %d\n", count++);
    if(!*head) { //list is empty
        //printf("\tInsert %d, branch 1\n", count++);
        *head = malloc(sizeof(Node));
        strcpy((*head)->word, word);
        (*head)->next = NULL;
        if(fromLR) {
            (*head)->rbCount = 0;
            (*head)->lrCount = 1;
        }
        else {
            (*head)->rbCount = 1;
            (*head)->lrCount = 0;
        }
    }
    else {
        //printf("\tInsert %d, branch 2\n", count++);
        Node *scan = *head, *prev = NULL;
        while(scan && compare(scan->word, word) < 0) {
            prev = scan;
            scan = scan->next;
        }
        //printf("\tInsert %d, branch 2\n", count++);
        if(scan && !compare(scan->word, word)) { //word has an existing node
            if(fromLR) {
                scan->lrCount++;
            }
            else {
                scan->rbCount++;
            }
        }
        else { //Word has no existing node
            //printf("\tInsert %d, branch 2\n", count++);
            Node *new = malloc(sizeof(Node));
            strcpy(new->word, word);            
            if(fromLR) {
                new->rbCount = 0;
                new->lrCount = 1;
            }
            else {
                new->rbCount = 1;
                new->lrCount = 0;
            }
            if(scan == *head) {
                insertFirst(head, new);
            }
            else {
                new->next = scan;
                prev->next = new;
            }
        }
    }
}

/*********************************************************************
*Inserts the given node at the front of the linked list.
*
*@params:
* -**head: The address of the first node in the linked list.
* -*new: The given node to be inserted at the front of the list.
*********************************************************************/
void insertFirst(List **head, Node *new) {
    new->next = *head;
    *head = new;
}

/*********************************************************************
*Frees the data allocated to each node in the given linked list.
*
*@params:
* -**head: The address of the first node in the linked list.
*********************************************************************/
void freeList(List **head) {
    if(*head) {
        freeList(&(*head)->next);
    }
    free(*head);
    *head = NULL;
}