#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"
#include "scanner.h"
#include <assert.h>



int main(int argc, char *argv[]) {
  /*Current edges*/
  int edges[14][3] = {{1, 2, 51}, {1, 4, 26}, {2, 3, 89}, {3, 5, 63}, {4, 3, 47},
  {5, 6, 111}, {3, 6, 55}, {6, 7, 77}, {4, 7, 51}, {7, 8, 50}, {7, 9, 15}, {9, 10, 40},
  {9, 11, 50}, {10, 11, 34}};
  List neighbourList[11];
  for(int i = 0; i < 11; i++){
      neighbourList[i] = NULL;
  }
  for(int i = 0; i < 11; i++){
      neighbourList[i] = newList(edges, i+1);
  }
  for(int i = 0; i< 11; i++){
      printf("node : %d\n", i+1);
      printList(neighbourList[i]);
  }
  for(int i = 0; i < 11; i++){
      freeList(neighbourList[i]);
  }
  /*Removing the disruptions*/
  // int numberOfDisruptions=0;
  // scanf("%d", &numberOfDisruptions);
  // char *city1;
  // char *city2;
  // while(numberOfDisruptions != 0){
  //     city1 = readInput();
  //     city2 = readInput();
  //     removeEdge(city1, city2);
  //     numberOfDisruptions--;
  // }
  // city1 = readInput();
  // city2 = readInput();
  // while (city1[0] != '!') {
  //
  //   printPath(city1, city2);
  //   printDuration(city1, city2);
  //
  //   free(city1);
  //   free(city2);
  //   city1 = readInput();
  //   city2 = readInput();
  // }
  // free(city1);
  // free(city2);
  return 0;
}
