#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "scanner.h"
#include "graphs.h"

void dijkstra(List neighbourList[11], int startingNode){
    int positions[11];
    for(int i = 0; i < 11; i++){
        positions[11] = -1;
    }
    heapNodes dist[11];
    for(int i = 0; i < 11; i++){
        if(i == startingNode - 1){
            dist[i].pseudodistance = 0;
            dist[i].id = startingNode;
        }
        else {
            dist[i].pseudodistance = 99999;
            dist[i].id = i + 1;
        }
    }
    Heap toDoList = makeHeap();
    for(int i = 0; i < 11; i++){
        enqueue(dist[i], &toDoList);
    }
    while(!isEmptyHeap(toDoList)){
        heapNode u = removeMin(&toDoList);
        while(neighbourList[u.id - 1] != NULL){
            neighbourList[u.id - 1].weight >
        }
    }

}


int removeMin(Heap *hp){
    int n;
    if(isEmptyHeap(*hp)){
        heapEmptyError();
    }
    n = hp->array[1];
    hp->front--;
    hp->array[1] = hp->array[front];
    downheap(hp, 1);
    return n;
}

void swap(int *a, int *b){
    int h = *a;
    *a = *b;
    *b = h;
}

void downheap (Heap *hp, int n){
    int fr = hp->front ;
    int indexMax = n ;
    if ( fr < 2* n +1 ) { /* node n is a leaf , so nothing to do */
        return ;
    }
    if (hp->array[n] < hp->array[2*n]) {
        indexMax = 2* n ;
    }
    if (fr > 2* n +1 && hp->array[indexMax] < hp->array[2*n+1]) {
        indexMax = 2* n +1;
    }
    if (indexMax != n) {
        swap (&( hp->array[n]),&(hp->array[indexMax]));
        downheap(hp,indexMax);
    }
}

void upheap(Heap *hp, int n){
    if(n > 1 && hp->array[n] < hp->array[n/2]){
        swap(hp->array[n], hp->array[n/2]);
        upheap(hp, n/2);
    }
}

void doubleHeapSize(Heap *hp){
    int newSize = 2 * hp->size;
    hp->array = realloc(hp->array, newSize * sizeof(int));
    assert(hp->array != NULL);
    hp->size = newSize;
}

Heap makeHeap(){
    Heap h;
    h.array = malloc(1 * sizeof(struct heapNode));
    assert(h.array != NULL);
    h.front = 1;
    h.size = 1;
    return h;
}

int isEmptyHeap(Heap h){
    return (h.front == 1);
}

void enqueue(int n, Heap *hp){
    int front = hp->front;
    if(front == hp->size){
        doubleHeapSize(hp);
    }
    hp->array[front] = n;
    upheap(hp, fr);
    hp->front = front + 1;
}

void heapEmptyError(){
    printf("heap empty\n");
    abort();
}

List newNode(int node, int weight){
    List new = malloc(sizeof(struct ListNode));
    new->weight = weight;
    new->node = node;
    new->next = NULL;
    return new;
}

List newList(int edges[14][3], int node){
    List li = NULL;
    List nodeList = NULL;
    List lastNode = NULL;
    for(int i = 0; i < 14; i++){
        if(edges[i][0] == node || edges[i][1] == node){
            if(edges[i][0] == node){
                nodeList = newNode(edges[i][1], edges[i][2]);
            }
            if(edges[i][1] == node){
                nodeList = newNode(edges[i][0], edges[i][2]);
            }
            if(lastNode == NULL) li = nodeList;
            else lastNode->next = nodeList;
            lastNode = nodeList;
        }
    }
    return li;
}

void printList(List list){
    while(list != NULL){
        printf("neighbour: %d\tweight: %d\n", list->node, list->weight);
        list = list->next;
    }
}

void freeList(List list){
    if(list == NULL) return;
    freeList(list->next);
    free(list);
}
