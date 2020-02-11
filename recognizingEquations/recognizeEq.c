#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "recognizeExp.h"
#include "recognizeEq.h"

void recognizeEquations() {
  char *ar;
  List tl, tl1;
  printf("give an equation: ");
  ar = readInput();
  while (ar[0] != '!') {
    tl = tokenList(ar);
    printf("the token list is ");
    printList(tl);
    tl1 = tl;
    if (acceptExpression(&tl1) && tl1 == NULL) {
      printf("this is an equation\n");
    } else {
      printf("this is not an equation\n");
    }
    free(ar);
    freeTokenList(tl);
    printf("\ngive an equation: ");
    ar = readInput();
  }
  free(ar);
  printf("good bye\n");
}
