#ifndef TRAINS_H
#define TRAINS_H

#include "scanner.h"

typedef struct heapNode {
  int cityID;
  int pDistance;
  int prevNode;
} heapNode;

typedef struct Heap {
    heapNode *array;
    int front;
    int size;
} Heap;

Heap makeHeap();

int isEmptyHeap(Heap h);

void heapEmptyError();

void enqueue(heapNode n, Heap *hp);

heapNode removeMin(Heap *hp);

void doubleHeapSize(Heap *hp);

void swap(heapNode *x, heapNode *y);

int cityToID(char *city);

void upheap(Heap *hp, int n);

void downheap(Heap *hp, int n);

void printID(int id);

void printy(Heap hp);

int getHeapPosition(Heap hp, int cityID);

void dijkstra(int matrix[11][11], int start, int end);

void printNode(heapNode n);

heapNode peekMin(Heap *hp);

void disruptor(int matrix[11][11], int city1, int city2);

#endif
