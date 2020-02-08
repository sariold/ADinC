/* file: signals.c */
/* date: 5/2/20 */
/* version: 2.4 */
/* Description: Extra task from the digital signals assignment. Reads in signal
input and returns the original input. */

#include <stdio.h>
#include <stdlib.h>
#include "LibStack.h"

void printSignal(int length) {
    int total = length;
    /* Three stacks: for starting intervals, ending intervals, and the value */
    Stack start, end, values;
    start = newStack(length);
    end = newStack(length);
    values = newStack(length);
    int max = 0;
    int startPos, endPos, number;
    while(length > 0) {
        scanf("[%d,%d)@%d ", &startPos, &endPos, &number);
        /* Determining the max end inteveral, which reveals the number of total
        values from the original input */
        if(endPos > max) max = endPos;
        push(startPos, &start);
        push(endPos, &end);
        push(number, &values);
        length--;
    }
    int *array = calloc(max, sizeof(int));
    printf("%d\n", max);
    /* While loop that pops the top value off of each of the three stacks */
    while(total > 0) {
        int startInterval = pop(&start);
        int endInterval = pop(&end);
        int temp = pop(&values);
        /* Fills up the array with latest popped value if it is greater than
        the value already placed in the array position */
        for(; startInterval < endInterval; startInterval++) {
            if(temp > array[startInterval]) array[startInterval] = temp;
        }
        total--;
    }
    /* Prints out the entire array of values */
    for(int k = 0; k < max; k++) {
        printf("%d ", array[k]);
    }
    printf("\n");
    freeStack(start);
    freeStack(end);
    freeStack(values);
    free(array);
}

/* Main function that reads in total number of signals, uses a while loop to
return the original signal input from each set of intervals. */
int main(int argc, char const *argv[]) {
    int totalSignals = 0;
    scanf("%d", &totalSignals);
    printf("%d\n", totalSignals);
    while(totalSignals > 0) {
        int length = 0;
        /* Length of intervals for each signal */
        scanf("%d\n", &length);
        printSignal(length);
        totalSignals--;
    }
    return 0;
}
