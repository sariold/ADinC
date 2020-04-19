#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"
#include "trains.h"

void printAr(int ar[11][11]) {
    for(int i = 0; i < 11; i++) {
        printf("{%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d}\n",
        ar[i][0], ar[i][1], ar[i][2], ar[i][3], ar[i][4], ar[i][5], ar[i][6],
        ar[i][7], ar[i][8], ar[i][9], ar[i][10]);
    }
}

int main(int argc, char *argv[]) {
    int disruptions = 0;
    int matrix[11][11] = {
        {-1, 34, 40 ,0, 0, 0 ,0 ,0 ,0 ,0 ,0},
        {34, -1, 50, 0, 0, 0, 0, 0, 0, 0, 0},
        {40, 50, -1, 15, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 15, -1, 50, 77, 51, 0, 0, 0, 0},
        {0, 0, 0, 50, -1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 77, 0, -1, 0, 0, 0, 55, 111},
        {0, 0, 0, 51, 0, 0, -1, 26, 0, 47, 0},
        {0, 0, 0, 0, 0, 0, 26, -1, 51, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 51, -1, 89, 0},
        {0, 0, 0, 0, 0, 55, 47, 0, 0, -1, 63},
        {0, 0, 0, 0, 0, 111, 0, 0, 0, 63, -1}
    };
    // printAr(matrix);
    printf("\n");
    scanf("%d\n", &disruptions);
    char *city1;
    char *city2;
    while(disruptions > 0) {
        // printf("%d\n", disruptions);
        city1 = readInput();
        city2 = readInput();
        disruptions-=1;
        // printID(cityToID(city1));
        // printID(cityToID(city2));
        disruptor(matrix, cityToID(city1), cityToID(city2));
        free(city1);
        free(city2);
    }
    // printAr(matrix);
    city1 = readInput();
    city2 = readInput();
    while(1) {
        dijkstra(matrix, cityToID(city1), cityToID(city2));
        free(city1);
        free(city2);
        city1 = readInput();
        if(city1[0] == '!') break;
        city2 = readInput();
    }
    free(city1);
return 0;
}
