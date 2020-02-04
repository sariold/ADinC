/* file: digitalSignals.c */
/* author: Diego Sariol (email: d.r.sariol@student.rug.nl)
            Rares Dobre (email: r.a.dobre@student.rugl.nl) */
/* date: 4/2/20 */
/* version: 1.0 */
/* Description: */

#include <stdio.h>
#include <stdlib.h>

#include "LibStack.h"

void stackReader(Stack *stack, int size) {
    int value = 0;
    int max = 0;
    printf("size:%d | ", size);
    while(size > 0) {
        scanf("%d", &value);
        if(value > max) max = value;
        push(value, stack);
        size--;
    }
    printf("max:%d\n", max);
}

void stackMakers(int total) {
    int size = 0;
    while(total > 0) {
        scanf("%d", &size);
        Stack stacko = newStack(size);
        stackReader(&stacko, size);
        total--;
    }
}

int main(int argc, char *argv[]) {
    int totalSignals = 0;
    scanf("%d", &totalSignals);
    stackMakers(totalSignals);
    return 0;
}
