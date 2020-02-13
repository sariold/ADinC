#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL */
#include "scanner.h"
#include "recognizeExp.h"
#include "recognizeEq.h"
#include <string.h>
#include "solveEq.h"

double solve(List li){
    double var;
    int varLeftSideX=0, varLeftSide=0, varRightSideX=0, varRightSide=0, value;
    while(li != NULL){
        if(li->tt == Symbol){
            if(li->t.symbol == '-'){
                li = li->next;
                if(li->tt == Number){
                    value = -1 * li->t.number;
                    li = li->next;
                    if(li->tt == Identifier){
                        varLeftSideX += value;
                    }
                    else varLeftSide += value;
                }
                if(li->tt == Identifier){
                    varLeftSideX -= 1;
                }
            }
        }
    }
    printf("\t%d\t%d\n", varLeftSideX, varLeftSide);
    return 5.0;
}


void solveEquations(){
    char *ar;
    List tl, tl1;
    printf("give an equation: ");
    ar = readInput();
    while (ar[0] != '!') {
      tl = tokenList(ar);
      printList(tl);
      tl1 = tl;
      if (acceptEquations(&tl1) && tl1 == NULL) {
        printf("this is an equation");
        if(variableCounter(tl)){
            printf(", but not in 1 variable\n");
        }
        else printf(" in 1 variable of degree %d\nsolution: %.3lf", degree(tl),
    solve(tl));
      }
      else {
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
