#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
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
of cities starts from 1, not 0.
*/

/*Function that converts strings (city names) to integers*/
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

/*Function to print the name of a city based on the id*/
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

/*Function to read the input of city names*/
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

/*Function that given a heap and a city id, returns the position in the heap
array of the city that matches the id */
int getHeapLocation(Heap hp, int city){
    int location = 0;
    for(int i = 0; i < hp.front; i++){
        if((hp.array[i]).id == city) location = i;
    }
    return location;
}

/*Function that computes the minimal distance from a starting node to an
ending node and outputs the shortest path*/
void dijkstra(List neighbourList[11], int startingNode, int endingNode){
    int path[11];
    int visited[11];
    /*Initialize the path and visited arrays*/
    for(int i = 0; i < 11; i++){
        path[i] = -1;
        visited[i] = 0;
    }
    heapNode dist[11];
    for(int i = 0; i < 11; i++){
        if(i == startingNode - 1){
            /*The pseudodistance of the starting node is set to 0*/
            dist[i].pseudodistance = 0;
            dist[i].id = startingNode;
        }
        else {
            /*The pseudodistance of other nodes is set to 99999*/
            dist[i].pseudodistance = 99999;
            dist[i].id = i + 1;
        }
    }
    /*Initializing the toDoList with nodes from the dist array. This is used
    to implement a min-priority queue based on the pseudodistances of nodes*/
    Heap toDoList = makeHeap();
    for(int i = 0; i < 11; i++){
        enqueue(dist[i], &toDoList);
    }
    while(!isEmptyHeap(toDoList)){
        heapNode u = removeMin(&toDoList);
        /*Removed a node where the initial pseudodistance was not updated,
        so it is unreachable*/
        if(u.pseudodistance == 99999) break;
        /*Mark the node as visited*/
        visited[u.id - 1] = 1;
        /*Ending node found*/
        if(u.id == endingNode){
            /*Reconstruct the path and output the distance*/
            reconstructPath(path, endingNode, startingNode);
            printf("%d\n", u.pseudodistance);
            free(toDoList.array);
            return;
        }
        List li = neighbourList[u.id - 1];
        /*Check all the neighbours of the removed node*/
        while(li != NULL){
            int neighbourLocation = getHeapLocation(toDoList, li->node);
            if(visited[li->node - 1] == 0 && (toDoList.array[neighbourLocation]).pseudodistance > u.pseudodistance + li->weight){
                /*Shorter path found, update the pseudodistance*/
                (toDoList.array[neighbourLocation]).pseudodistance = u.pseudodistance + li->weight;
                path[li->node - 1] = u.id;
                /*Upheap to restore the order*/
                upheap(&toDoList, neighbourLocation);
            }
            /*Move to the next neighbour*/
            li = li->next;
        }
    }
    /*Unreachable node found, output UNREACHABLE and free the heap*/
    printf("UNREACHABLE\n");
    free(toDoList.array);
}

/*Function that given an ending node and a starting node, it outputs the
shortest path from the starting node to the ending node*/
void reconstructPath(int path[11], int node, int start){
    int ar[11], j=0;
    for(int i = 0; i < 11; i++){
        ar[i] = -1;
    }
    while(node != start){
        /*Backtrack the path and add the id's to the array ar*/
        ar[j] = node;
        j++;
        node = path[node - 1];
    }
    ar[j] = node;
    /*Print the path*/
    for(int i = 10; i >= 0; i--){
        if(ar[i] != -1){
            printCityFromId(ar[i]);
        }
    }
}

/*Removes the minimum node from the heap*/
heapNode removeMin(Heap *hp){
    heapNode n;
    if(isEmptyHeap(*hp)){
        heapEmptyError();
    }
    n = hp->array[1];
    hp->front--;
    /*Set the first node to the last one*/
    hp->array[1] = hp->array[hp->front];
    /*Downheap to restore order*/
    downheap(hp, 1);
    return n;
}

void swap(heapNode *a, heapNode *b){
    heapNode h = *a;
    *a = *b;
    *b = h;
}

/*Function to downheap nodes in a heap based on their pseudodistance*/
void downheap (Heap *hp, int n){
    int fr = hp->front ;
    int indexMax = n ;
    if ( fr < 2* n +1 ) { /* node n is a leaf , so nothing to do */
        return ;
    }
    if (hp->array[n].pseudodistance > hp->array[2*n].pseudodistance) {
        indexMax = 2* n ;
    }
    if (fr > 2 * n + 1 && hp->array[indexMax].pseudodistance > hp->array[2*n+1].pseudodistance) {
        indexMax = 2* n +1;
    }
    if (indexMax != n) {
        swap (&( hp->array[n]),&(hp->array[indexMax]));
        downheap(hp,indexMax);
    }
}

/*Function to upheap ndoes in a heap based on their pseudodistance*/
void upheap(Heap *hp, int n){
    if(n > 1 && (hp->array[n]).pseudodistance < (hp->array[n/2]).pseudodistance){
        swap(&hp->array[n], &hp->array[n/2]);
        upheap(hp, n/2);
    }
}

/*Doubles the heap size*/
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

/*Function to enqueue a node to the heap*/
void enqueue(heapNode n, Heap *hp){
    int front = hp->front;
    if(front == hp->size){
        doubleHeapSize(hp);
    }
    hp->array[front] = n;
    /*Upheap to restore the order*/
    upheap(hp, front);
    hp->front = front + 1;
}

void heapEmptyError(){
    printf("heap empty\n");
    abort();
}

/*Function to create a new graph node given a node id and the weight to it*/
List newNode(int node, int weight){
    List new = malloc(sizeof(struct ListNode));
    new->weight = weight;
    new->node = node;
    new->next = NULL;
    return new;
}

/*Function to create the list of neighbours for a node, given the matrix of edges
and the specific node*/
List newList(int edges[14][3], int node){
    List li = NULL;
    List nodeList = NULL;
    List lastNode = NULL;
    for(int i = 0; i < 14; i++){
        /*There is an edge incident with the given node*/
        if(edges[i][0] == node || edges[i][1] == node){
            if(edges[i][0] == node){
                nodeList = newNode(edges[i][1], edges[i][2]);
            }
            if(edges[i][1] == node){
                nodeList = newNode(edges[i][0], edges[i][2]);
            }
            /*List was empty, add first node*/
            if(lastNode == NULL) li = nodeList;
            /*There is already a list, append the node to the end*/
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

/*Function that given two endpoints of an edge, "deletes" the edge from the
edges array*/
void disruptor(int ar[14][3], int city1, int city2) {
    for(int i = 0; i < 14; i++) {
        if((ar[i][0] == city1 && ar[i][1] == city2) ||
        (ar[i][0] == city2 && ar[i][1] == city1)) {
            /*Set the two endpoints in the edges array to -1*/
            ar[i][0] = -1;
            ar[i][1] = -1;
        }
    }
}

void printy(int ar[14][3]) {
    for(int i = 0; i < 14; i++) {
        if(ar[i][0] != -1 && ar[i][1] != -1){
            printf("{");
            printCityFromId(ar[i][0]);
            printf(",");
            printCityFromId(ar[i][1]);
            printf(",");
            printf("%d}\n", ar[i][2]);
        }
    }
}
