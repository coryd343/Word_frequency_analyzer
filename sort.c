/*
* Sort: Object file for use with HW6
* Author: Cory Davis
* Version: 5/21/17
*/

#include "sort.h"
#include "linkedlist.h"


/*********************************************************************
*Performs a merge sort on the given linked list according to a
*specified comparator.
*
*@params:
* -**head: The address of the first node in the linked list.
* -*compare: A pointer to the specified comparator function.
*********************************************************************/
void mergeSort(List **head, int (*compare)(const void *p1, const void *p2)) {
    int count = 1;
    List *leftStart = *head;
    if(leftStart && leftStart->next) {
        List *leftEnd = *head, *rightStart = *head, *last = *head, *temp = NULL, *tHead = NULL, *tLast = NULL;
        
        while(last && last->next) {
            leftEnd = rightStart;
            rightStart = rightStart->next;
            last = last->next->next;
        }
        leftEnd->next = NULL;
        mergeSort(&leftStart, compare);
        mergeSort(&rightStart, compare);
        *head = merge(&leftStart, &rightStart, &temp, &tHead, &tLast, compare);
    }
}

/*********************************************************************
*Merges two halves of a linked list back into one.
*
*@params:
* -**left: The node at the front of the left half.
* -**right: The node at the front of the right half.
* -**temp: The node which selects the next sorted index.
* -**head: Stores the first node in the reconstructed list.
* -**tail: Stores the last node in the reconstructed list.
* -*compare: A pointer to the specified comparator function.
*********************************************************************/
List *merge(List **left, List **right, List **temp, List **head, List **tail, int (*compare)(const void *p1, const void *p2)) {
    int count = 1;
    while(*left || *right) {
        if(!*right) {
            *temp = *left;
            *left = (*left)->next;
        }
        else if(!*left) {
            *temp = *right;
            *right = (*right)->next;
        }
        else if(compare(*left, *right) > 0) {
            *temp = *left;
            *left = (*left)->next;
        }
        else {
            *temp = *right;
            *right = (*right)->next;
        }
        if(!*head) {
            *head = *temp;
        }
        else {
            (*tail)->next = *temp;
        }
        *tail = *temp;
    }
    return *head;
}