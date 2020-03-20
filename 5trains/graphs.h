#ifndef GRAPHS_H
#define GRAPHS_H

#include "scanner.h"

typedef struct ListNode *List;

typedef struct ListNode {
  int node;
  int weight;
  List next;
} ListNode;

typedef struct heapNode {
    int id;
    int pseudodistance;
} heapNode;

typedef struct Heap {
    heapNode *array;
    int size;
    int front;
}   Heap;

char *readInput();

void printHeap(Heap hp);

heapNode removeMin(Heap *hp, int *location);

void swap(heapNode *a, heapNode *b);

void downheap (Heap *hp, int *n);

void upheap(Heap *hp, int *n);

void doubleHeapSize(Heap *hp);

Heap makeHeap();

int isEmptyHeap(Heap h);

void enqueue(heapNode n, Heap *hp, int *location);

void heapEmptyError();

List newNode(int node, int weight);

List newList(int arr[14][3], int node);

void printList(List list);

void freeList(List list);

void dijkstra(List neighbourList[11], int startingNode, int endingNode);

int getHeapLocation(Heap hp, int city);


#endif
