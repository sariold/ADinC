/* file: digitalSignals.c */
/* author: Rares Dobre (email: r.a.dobre@student.rugl.nl)
            Diego Sariol (email: d.r.sariol@student.rug.nl) */
/* date: 4/2/20 */
/* version: 4.2 */
/* Description: */

#include <stdio.h>
#include <stdlib.h>
#include "LibStack.h"

void printSignal(int length){
    Stack st, stp;
    st = newStack(length);
    stp = newStack(length);
    int i=1, value=0;
    scanf("%d", &value);
    for(int j=1; j<=value; j++){
        push(j, &st);
        push(0, &stp);
    }
    for(; i<length; i++){
        scanf("%d", &value);
        if(isEmptyStack(st)){                  //FIX FOR BUG
            for(int j=1; j<=value; j++){
                push(j, &st);
                push(i, &stp);
            }
        }
        if(st.top > 0 && value > st.array[st.top - 1]) {
            int sentinel = st.array[st.top - 1];
            while (value - sentinel > 0){
                    sentinel++;
                    push(sentinel, &st);
                    push(i, &stp);
            }
        }
        if(st.top > 0 && value < st.array[st.top - 1]){
            while(st.top>0 && st.array[st.top - 1] > value){
                printf("[%d,%d)@%d ", pop(&stp), i, pop(&st));
            }
        }
    }
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
