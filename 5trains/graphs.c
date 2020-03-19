#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "scanner.h"
#include "graphs.h"

int getHeapLocation(Heap hp, int city){
    int location;
    for(int i = 0; i < hp.front; i++){
        if(i+1 == city) location = i;
    }
    return location;
}

void dijkstra(List neighbourList[11], int startingNode, int endingNode){
    int positions[11];
    int visited[11];
    for(int i = 0; i < 11; i++){
        positions[i] = -1;
        visited[i] = 0;
    }
    heapNode dist[11];
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
        if(u.id == endingNode){
            printf("startingNode: %d\tendingNode:%d\tdistance:%d\n", startingNode, endingNode, u.pseudodistance);
            return;
        }
        visited[u.id - 1] = 1;
        while(neighbourList[u.id - 1] != NULL){
            int neighbourLocation = getHeapLocation(toDoList, neighbourList[u.id - 1]->node);
            if((toDoList.array[neighbourLocation]).pseudodistance > u.pseudodistance + neighbourList[u.id - 1]->weight){
                (toDoList.array[neighbourLocation]).pseudodistance = u.pseudodistance + neighbourList[u.id - 1]->weight;
                upheap(&toDoList, neighbourLocation);
            }
            // else if (neighbourList[u.id - 1].weight >  ){
            //
            // }
        }
    }

}


heapNode removeMin(Heap *hp){
    heapNode n;
    if(isEmptyHeap(*hp)){
        heapEmptyError();
    }
    n = hp->array[1];
    hp->front--;
    hp->array[1] = hp->array[hp->front];
    downheap(hp, 1);
    return n;
}

void swap(heapNode *a, heapNode *b){
    heapNode h = *a;
    *a = *b;
    *b = h;
}

void downheap (Heap *hp, int n){
    int fr = hp->front ;
    int indexMax = n ;
    if ( fr < 2* n +1 ) { /* node n is a leaf , so nothing to do */
        return ;
    }
    if (hp->array[n].pseudodistance < hp->array[2*n].pseudodistance) {
        indexMax = 2* n ;
    }
    if (fr > 2 * n + 1 && hp->array[indexMax].pseudodistance < hp->array[2*n+1].pseudodistance) {
        indexMax = 2* n +1;
    }
    if (indexMax != n) {
        swap (&( hp->array[n]),&(hp->array[indexMax]));
        downheap(hp,indexMax);
    }
}

void upheap(Heap *hp, int n){
    if(n > 1 && hp->array[n].pseudodistance < hp->array[n/2].pseudodistance){
        swap(&hp->array[n], &hp->array[n/2]);
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

void enqueue(heapNode n, Heap *hp){
    int front = hp->front;
    if(front == hp->size){
        doubleHeapSize(hp);
    }
    hp->array[front] = n;
    upheap(hp, front);
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
