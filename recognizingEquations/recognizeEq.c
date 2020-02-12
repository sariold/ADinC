#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include "recognizeExp.h"
#include "recognizeEq.h"

// acceptNumber
// acceptIdentifi{er
// acceptCharacter

// int varCounter(List *lp) {
//
// }

int acceptTermEq(List *lp) {
    while(1) {
        if(*lp == NULL) return 0;
        if(acceptCharacter(lp, '=')) return 0;
        if(acceptNumber(lp)) {
            if(acceptIdentifier(lp)) {
                if(acceptCharacter(lp, '^')) {
                    if(acceptNumber(lp)) return 1;
                     else return 0;
                }
                return 1;
            }
            return 1;
        }
        if(acceptIdentifier(lp)) {
            if(acceptCharacter(lp, '^')) {
                if(acceptNumber(lp)) return 1;
                else return 0;
            }
            return 1;
        }
    }
}

int acceptExpressionEq(List *lp) {
    if(acceptCharacter(lp, '-')) {
        if (!acceptTermEq(lp)) {
            printf("term failed\n");
          return 0;
        }
    }
  else if (!acceptTermEq(lp)) {
      printf("term failed\n");
    return 0;
  }
  while (acceptCharacter(lp, '+') || acceptCharacter(lp, '-')) {
    if (!acceptTermEq(lp)) {
      return 0;
    }
  }
  return 1;
}

int acceptEquation(List *lp) {
  return (acceptExpressionEq(lp) && acceptCharacter(lp, '=') && acceptExpressionEq(lp));
}

void recognizeEquations() {
    int degree = -1;
  char *ar;
  List tl, tl1;
  printf("give an equation: ");
  ar = readInput();
  while (ar[0] != '!') {
    tl = tokenList(ar);
    printf("the token list is ");
    printList(tl);
    tl1 = tl;
    if (acceptEquation(&tl1) && tl1 == NULL) {
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
