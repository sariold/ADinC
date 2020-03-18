#ifndef GRAPHS_H
#define GRAPHS_H

#include "scanner.h"

typedef struct ListNode *List;

typedef struct ListNode {
  int node;
  int weight;
  List next;
} ListNode;

typedef struct Heap {
    heapNode *array;
    int size;
    int front;
}   Heap;

typedef struct heapNode {
    int id;
    int pseudodistance;
} heapNode;


int removeMin(Heap *hp);

void swap(int *a, int *b);

void downheap (Heap *hp, int n);

void upheap(Heap *hp, int n);

void doubleHeapSize(Heap *hp);

Heap makeHeap();

int isEmptyHeap(Heap h);

void enqueue(int n, Heap *hp);

void heapEmptyError();

List newNode(int node, int weight);

List newList(int arr[14][3], int node);

void printList(List list);

void freeList(List list);



#endif
