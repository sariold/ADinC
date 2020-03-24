#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"
#include <assert.h>

int main(int argc, char *argv[]) {
  /*Matrix that holds all the given edges, first two columns indicate the
  incident nodes, third column indicates the weight of the edge*/
  int edges[14][3] = {{1, 2, 51}, {1, 4, 26}, {2, 3, 89}, {3, 5, 63}, {4, 3, 47},
  {5, 6, 111}, {3, 6, 55}, {6, 7, 77}, {4, 7, 51}, {7, 8, 50}, {7, 9, 15}, {9, 10, 40},
  {9, 11, 50}, {10, 11, 34}};
  List neighbourList[11];
  char *city1;
  char *city2;
  for(int i = 0; i < 11; i++){
      neighbourList[i] = NULL;
  }
  int disruptions = 0;
  scanf("%d\n", &disruptions);
  while(disruptions > 0) {
          /*Read in disruptions*/
          city1 = readInput();
          city2 = readInput();
          int cityID1 = cityToId(city1);
          int cityID2 = cityToId(city2);
          free(city1);
          free(city2);
          disruptions -= 1;
          disruptor(edges, cityID1, cityID2);
  }
  for(int i = 0; i < 11; i++){
      /*Create the adjacency list for each node*/
      neighbourList[i] = newList(edges, i+1);
  }
  city1 = readInput();
  city2 = readInput();
  while (city1[0] != '!' && city2[0] != '!') {
    /*Find the shortest path from city1 to city2*/
    dijkstra(neighbourList, cityToId(city1), cityToId(city2));
    free(city1);
    free(city2);
    /*Read in the next query*/
    city1 = readInput();
    if(city1[0] == '!') break;
    city2 = readInput();
  }
  /*Free the adjacency lists*/
  for(int i = 0; i < 11; i++){
      freeList(neighbourList[i]);
  }
  free(city1);
  return 0;
}
