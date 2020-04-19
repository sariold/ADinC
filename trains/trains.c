#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "scanner.h"
#include "trains.h"

Heap makeHeap() {
    Heap h;
    h.array = malloc(1 * sizeof(heapNode));
    assert(h.array != NULL);
    h.front = 1;
    h.size = 1;
    return h;
}

int isEmptyHeap(Heap h) {
    return (h.front == 1);
}

void heapEmptyError() {
    printf("heap empty\n");
    abort();
}

void enqueue(heapNode n, Heap *hp) {
    int fr = hp->front;
    if(fr == hp->size) {
        doubleHeapSize(hp);
    }
    hp->array[fr] = n;
    upheap(hp, fr);
    hp->front = fr + 1;
}

heapNode removeMin(Heap *hp) {
    heapNode n;
    if(isEmptyHeap(*hp)) {
        heapEmptyError();
    }
    n = hp->array[1];
    hp->front--;
    hp->array[1] = hp->array[hp->front];
    downheap(hp, 1);
    return n;
}

heapNode peekMin(Heap *hp) {
    heapNode n;
    if(isEmptyHeap(*hp)) {
        heapEmptyError();
    }
    n = hp->array[1];
    return n;
}

void doubleHeapSize(Heap *hp) {
    int new = 2 * hp->size;
    hp->array = realloc(hp->array, new * sizeof(heapNode));
    assert(hp->array != NULL);
    hp->size = new;
}

void swap(heapNode *x, heapNode *y) {
    heapNode h = *x;
    *x = *y;
    *y = h;
}

void upheap(Heap *hp, int n) {
    if(n > 1 && hp->array[n].pDistance < hp->array[n/2].pDistance) {
        swap(&(hp->array[n]), &(hp->array[n/2]));
        upheap(hp, n/2);
    }
}

void downheap(Heap *hp, int n) {
    int fr = hp->front;
    int indexMax = n;
    if(fr < 2 * n + 1) return;
    if(hp->array[n].pDistance > hp->array[2 * n].pDistance) indexMax = 2 * n;
    if(fr > 2 * n + 1 && hp->array[indexMax].pDistance
        > hp->array[2 * n + 1].pDistance) {
        indexMax = 2 * n + 1;
    }
    if(indexMax != n) {
        swap(&(hp->array[n]), &(hp->array[indexMax]));
        downheap(hp, indexMax);
    }
}

void printID(int id) {
    switch(id) {
        case 0:
            printf("Leeuwarden\n");
            break;
        case 1:
            printf("Groningen\n");
            break;
        case 2:
            printf("Meppel\n");
            break;
        case 3:
            printf("Zwolle\n");
            break;
        case 4:
            printf("Enschede\n");
            break;
        case 5:
            printf("Nijmegen\n");
            break;
        case 6:
            printf("Utrecht\n");
            break;
        case 7:
            printf("Amsterdam\n");
            break;
        case 8:
            printf("Den Haag\n");
            break;
        case 9:
            printf("Eindhoven\n");
            break;
        case 10:
            printf("Maastricht\n");
            break;
    }
}

int cityToID(char *city) {
    char leeuwarden[11] = "Leeuwarden";
    char groningen[10] = "Groningen";
    char meppel[7] = "Meppel";
    char zwolle[7] = "Zwolle";
    char enschede[9] = "Enschede";
    char nijmegen[9] = "Nijmegen";
    char utrecht[8] = "Utrecht";
    char amsterdam[10] = "Amsterdam";
    char denHaag[9] = "Den Haag";
    char eindhoven[10] = "Eindhoven";
    char maastricht[11] = "Maastricht";
    if(strcmp(city, leeuwarden) == 0) return 0;
    if(strcmp(city, groningen) == 0) return 1;
    if(strcmp(city, meppel) == 0) return 2;
    if(strcmp(city, zwolle) == 0) return 3;
    if(strcmp(city, enschede) == 0) return 4;
    if(strcmp(city, nijmegen) == 0) return 5;
    if(strcmp(city, utrecht) == 0) return 6;
    if(strcmp(city, amsterdam) == 0) return 7;
    if(strcmp(city, denHaag) == 0) return 8;
    if(strcmp(city, eindhoven) == 0) return 9;
    if(strcmp(city, maastricht) == 0) return 10;
    return -1;
}

int getHeapPosition(Heap hp, int cityID) {
    int position = 0;
    // printf("hp.front:%d\n", hp.front);
    for(int i = 1; i < hp.front; i++) {
        // printID(hp.array[i].cityID);
        if((hp.array[i]).cityID == cityID) position = i;
    }
    return position;
}

void printy(Heap hp) {
    for(int i = 1; i < hp.front; i++) {
        printf("(");
        printID(hp.array[i].cityID);
        printf("pDis:%d, ", hp.array[i].pDistance);
        printf("pN:");
        printID(hp.array[i].prevNode);
        printf(")");
        printf("\n\n");
    }
    printf("\n");
}

void printNode(heapNode n) {
    printID(n.cityID);
    printf("pDis:%d\n", n.pDistance);
    printID(n.prevNode);
}

void dijkstra(int matrix[11][11], int start, int end) {
    int *path = calloc(11, sizeof(int));
    Heap pQueue = makeHeap();
    Heap visited = makeHeap();
    for(int i = 0; i < 11; i++) {
        heapNode newNode;
        newNode.cityID = i;
        if(i == start) newNode.pDistance = 0;
        else newNode.pDistance = 9999;
        newNode.prevNode = -1;
        enqueue(newNode, &pQueue);
    }
    while(!isEmptyHeap(pQueue)) {
        int pos = 0;
        heapNode top = peekMin(&pQueue);
        if(top.pDistance == 9999) break;
        if(top.cityID != end) {
            heapNode min = removeMin(&pQueue);
            enqueue(min, &visited);
            printNode(min);
            // printy(pQueue);
            printf("----------------\n");
            for(int j = 0; j < 11; j++) {
                if(j != min.cityID && matrix[min.cityID][j] > 0) {
                    // printID(j);
                    // printf("j:%d & %d\n", j, matrix[min.cityID][j]);
                    pos = getHeapPosition(pQueue, j);
                    // if(pos == 0) break;
                    // pos = getHeapPosition(pQueue, 1);
                    // printf("pos:%d for %d\n", pos, j);
                    // printf("%d %d %d\n", min.pDistance, matrix[min.cityID][j],
                    // pQueue.array[pos].pDistance);
                    if(pos != 0) {
                        if(min.pDistance + matrix[min.cityID][j]
                            < pQueue.array[pos].pDistance) {
                                pQueue.array[pos].pDistance = min.pDistance
                                + matrix[min.cityID][j];
                                pQueue.array[pos].prevNode = min.cityID;
                                upheap(&pQueue, pos);
                        }
                    }
                }
            }
        }
        else if (top.cityID == end){
            int index = 0, totalDis = top.pDistance;
            path[0] = end;
            while(top.cityID != start) {
                index++;
                top = visited.array[getHeapPosition(visited, top.prevNode)];
                path[index] = top.cityID;
            }
            for(int k = index; k >= 0; k--) {
                printID(path[k]);
            }
            printf("%d\n", totalDis);
            free(pQueue.array);
            free(visited.array);
            free(path);
            return;
        }
    }
    printf("UNREACHABLE\n");
    free(pQueue.array);
    free(visited.array);
    free(path);
}

void disruptor(int matrix[11][11], int city1, int city2) {
    matrix[city1][city2] = -1;
    matrix[city2][city1] = -1;
}
