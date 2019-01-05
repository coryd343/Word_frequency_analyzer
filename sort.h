/*
* Sort Header: Object header file for use with HW6
* Author: Cory Davis
* Version: 5/21/17
*/

#ifndef SORT_H
#define SORT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

/*********************************************************************
*Performs a merge sort on the given linked list according to a
*specified comparator.
*
*@params:
* -**head: The address of the first node in the linked list.
* -*compare: A pointer to the specified comparator function.
*********************************************************************/
void mergeSort(List **, int (*compare)(const void *p1, const void *p2));

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
List *merge(List **, List **, List **, List **, List **, int (*compare)(const void *p1, const void *p2));
#endif