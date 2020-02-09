#include <stdio.h>
#include <stdlib.h>
#include "LibStack.h"

void printSignal(int length){
    Stack st, stp;
/*Create two stacks, st contains all the layers that are open. Stp
is another stack containing the starting positions of each layer. The
two stacks are kept in sync.*/
    st = newStack(length);
    stp = newStack(length);
    int i=1, value=0;
    scanf("%d", &value);
/*Push all the layers up untill the value that was read on the stack.
For example, reading 3 will result in pushing 1, 2 and 3 on the stack*/
    for(int j=1; j<=value; j++){
        push(j, &st);
        push(0, &stp);
    }
    for(; i<length; i++){
        scanf("%d", &value);
        if(isEmptyStack(st)){
            for(int j=1; j<=value; j++){
                push(j, &st);
                push(i, &stp);
            }
        }
/*3 possible cases: if the value is greater than the Top of the Stack,
push all layers up till that value on the stack and their corresponding
starting value on the positional stack; if the value is equal to the Top
of the Stack do nothing(the ending index is incremented)*/
        if(st.top > 0 && value > st.array[st.top - 1]) {
            int sentinel = st.array[st.top - 1];
            while (value - sentinel > 0){
                    sentinel++;
                    push(sentinel, &st);
                    push(i, &stp);
            }
        }
/*If the value is less than the Top of the Stack, layers are ending, so pop
the layers and their corresponding starting values and print them*/
        if(st.top > 0 && value < st.array[st.top - 1]){
            while(st.top>0 && st.array[st.top - 1] > value){
                printf("[%d,%d)@%d ", pop(&stp), i, pop(&st));
            }
        }
    }
/*Print the remaining open layers*/
    while(st.top != 0){
        printf("[%d,%d)@%d ", pop(&stp), i, pop(&st));
    }
    printf("\n");
    freeStack(st);
    freeStack(stp);
}

int main(int argc, char const *argv[]) {
    int n=0;
    scanf("%d", &n);
    while(n > 0){
        int length=0;
        scanf("%d", &length);
        printSignal(length);
        n--;
    }
    return 0;
}
