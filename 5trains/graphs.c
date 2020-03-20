#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "scanner.h"
#include "graphs.h"

/*
City ID's:
    Amsterdam: 1
    Den Haag: 2
    Eindhoven: 3
    Utrecht: 4
    Maastricht: 5
    Nijmegen: 6
    Zwolle: 7
    Enschede: 8
    Meppel: 9
    Leeuwarden: 10
    Groningen: 11
In certain functions we subtract 1 from the city id's, because the numbering
of cities starts from 1, not 0
*/

int cityToId(char *s){
    char amsterdam[10] = "Amsterdam";
    char haag[9] = "Den Haag";
    char eindhoven[10] = "Eindhoven";
    char utrecht[8] = "Utrecht";
    char maastricht[11] = "Maastricht";
    char nijmegen[9] = "Nijmegen";
    char zwolle[7] = "Zwolle";
    char enschede[9] = "Enschede";
    char meppel[7] = "Meppel";
    char leeuwarden[11] = "Leeuwarden";
    char groningen[10] = "Groningen";
    if(strcmp(s, amsterdam) == 0) return 1;
    if(strcmp(s, haag) == 0) return 2;
    if(strcmp(s, eindhoven) == 0) return 3;
    if(strcmp(s, utrecht) == 0) return 4;
    if(strcmp(s, maastricht) == 0) return 5;
    if(strcmp(s, nijmegen) == 0) return 6;
    if(strcmp(s, zwolle) == 0) return 7;
    if(strcmp(s, enschede) == 0) return 8;
    if(strcmp(s, meppel) == 0) return 9;
    if(strcmp(s, leeuwarden) == 0) return 10;
    if(strcmp(s, groningen) == 0) return 11;
    return 0;
}

void printCityFromId(int id){
    switch (id) {
        case 1:{
            printf("Amsterdam\n");
            break;
        }
        case 2:{
            printf("Den Haag\n");
            break;
        }
        case 3:{
            printf("Eindhoven\n");
            break;
        }
        case 4:{
            printf("Utrecht\n");
            break;
        }
        case 5:{
            printf("Maastricht\n");
            break;
        }
        case 6:{
            printf("Nijmegen\n");
            break;
        }
        case 7:{
            printf("Zwolle\n");
            break;
        }
        case 8:{
            printf("Enschede\n");
            break;
        }
        case 9:{
            printf("Meppel\n");
            break;
        }
        case 10:{
            printf("Leeuwarden\n");
            break;
        }
        case 11:{
            printf("Groningen\n");
            break;
        }
    }
}

char *readInput() {
  int strLen = 30;
  int c = getchar();
  int i = 0;
  char *s = malloc((strLen+1)*sizeof(char));
  assert( s != NULL );
  while ( c != '\n' ) {
    s[i] = c;
    i++;
    if ( i >= strLen ) { /* s is not large enough, its length is doubled */
      strLen = 2*strLen;
      s = realloc(s,(strLen+1)*sizeof(char));
      assert( s != NULL );
    }
    c = getchar();
  }
  s[i] = '\0';
  return s;
}

void printHeap(Heap hp){
    for(int i = 0; i < hp.front; i++){
        printf("| %d %d |", hp.array[i].id, hp.array[i].pseudodistance);
    }
    printf("\n");
}

int getHeapLocation(Heap hp, int city){
    int location;
    for(int i = 0; i < hp.front; i++){
        if((hp.array[i]).id == city) location = i;
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
        enqueue(dist[i], &toDoList, &positions[i]);
    }
    while(!isEmptyHeap(toDoList)){
        // printHeap(toDoList);
        heapNode u = removeMin(&toDoList, &positions[toDoList.front - 1]);
        // printf("removed node:%d\t pseudodistance:%d\n\n", u.id, u.pseudodistance);
        // printHeap(toDoList);
        visited[u.id - 1] = 1;
        if(u.id == endingNode){
            printf("startingNode: %d\tendingNode:%d\tdistance:%d\n", startingNode, endingNode, u.pseudodistance);
            return;
        }
        while(neighbourList[u.id - 1] != NULL){
            int neighbourLocation = positions[neighbourList[u.id - 1]->node - 1];
            // int neighbourLocation = getHeapLocation(toDoList, neighbourList[u.id - 1]->node);
            // printf("neighbour node in heap: %d\n", (toDoList.array[neighbourLocation]).id);
            // printf("neighbour: %d\n", neighbourList[u.id - 1]->node);
            if(visited[neighbourList[u.id - 1]->node - 1] == 0 &&  (toDoList.array[neighbourLocation]).pseudodistance > u.pseudodistance + neighbourList[u.id - 1]->weight){
                // printf("shorter path found: %d to node: %d\n", u.pseudodistance + neighbourList[u.id - 1]->weight, (toDoList.array[neighbourLocation]).id);
                (toDoList.array[neighbourLocation]).pseudodistance = u.pseudodistance + neighbourList[u.id - 1]->weight;
                upheap(&toDoList, &positions[neighbourList[u.id - 1]->node - 1]);
                // upheap(&toDoList, neighbourLocation);
                // printf("updated heap: ");
                // printHeap(toDoList);
            }
            neighbourList[u.id - 1] = neighbourList[u.id - 1]->next;
        }
    }
}


heapNode removeMin(Heap *hp, int *location){
    heapNode n;
    if(isEmptyHeap(*hp)){
        heapEmptyError();
    }
    n = hp->array[1];
    hp->front--;
    hp->array[1] = hp->array[hp->front];
    *location = 1;
    downheap(hp, location);
    return n;
}

void swap(heapNode *a, heapNode *b){
    heapNode h = *a;
    *a = *b;
    *b = h;
}

void downheap (Heap *hp, int *n){
    int fr = hp->front ;
    int indexMax = *n ;
    if (fr < 2 * (*n) + 1) { /* node n is a leaf , so nothing to do */
        return ;
    }
    if (hp->array[*n].pseudodistance > hp->array[2*(*n)].pseudodistance) {
        indexMax = 2 * (*n);
    }
    if (fr > 2 * (*n) + 1 && hp->array[indexMax].pseudodistance > hp->array[2*(*n)+1].pseudodistance) {
        indexMax = 2 * (*n) +1;
    }
    if (indexMax != (*n)) {
        swap (&( hp->array[*n]),&(hp->array[indexMax]));
        *n = indexMax;
        downheap(hp, n);
    }
}

void upheap(Heap *hp, int *n){
    if(*n > 1 && (hp->array[*n]).pseudodistance < (hp->array[(*n)/2]).pseudodistance){
        swap(&hp->array[*n], &hp->array[(*n)/2]);
        *n /= 2;
        upheap(hp, n);
    }
}

void doubleHeapSize(Heap *hp){
    int newSize = 2 * hp->size;
    hp->array = realloc(hp->array, newSize * sizeof(struct heapNode));
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

void enqueue(heapNode n, Heap *hp, int *location){
    int front = hp->front;
    if(front == hp->size){
        doubleHeapSize(hp);
    }
    hp->array[front] = n;
    *location = front;
    upheap(hp, location);
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
