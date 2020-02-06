#include <stdio.h>
#include <stdlib.h>
#include "LibStack.h"

void originalSignal(){
    int length=0, start, end, level, maxEnd=0, *signal;
    Stack startIndex, endIndex, levels;
    scanf("%d\n", &length);
    startIndex = newStack(length);
    endIndex = newStack(length);
    levels = newStack(length);
    while(length>0){
        scanf("[%d,%d)@%d ", &start, &end, &level);
        if(end>maxEnd) maxEnd = end;
        push(start, &startIndex);
        push(end, &endIndex);
        push(level, &levels);
        length--;
    }
    signal = calloc(maxEnd, sizeof(int));
    while(!isEmptyStack(startIndex)){
        start = pop(&startIndex);
        end = pop(&endIndex);
        level = pop(&levels);
        for(int i = start; i < end; i++){
            signal[i] = level;
        }
    }
    printf("%d\n", maxEnd);
    for(int i=0; i<maxEnd; i++){
        printf("%d ", signal[i]);
    }
    printf("\n");
    freeStack(startIndex);
    freeStack(endIndex);
    freeStack(levels);
}

int main(int argc, char *argv[]) {
    int n=0;
    scanf("%d", &n);
    printf("%d\n", n);
    for(int i=0; i<n; i++){
        originalSignal();
    }
    return 0;
}
