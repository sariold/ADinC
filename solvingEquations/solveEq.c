#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL */
#include <string.h>
#include "scanner.h"
#include "recognizeExp.h"
#include "recognizeEq.h"
#include "solveEq.h"

double solve(List li){
    double x = 0.0;
    int equalsDetected = 0, a=0, b=0;
// We get an equation in the form ax+b = cx+d, so we restrict it to ex+f=0
    if(acceptCharacter(&li, '=')) equalsDetected=1;
    if(acceptIdentifier(&li)){
        if(equalsDetected==0) a++;
        else a--;
    }
    if(li != NULL && li->tt == Number){
        int value = li->t.number;
        if(acceptIdentifier(&li)){
            if(equalsDetected==0) a += value;
            else a -= value;
        } else {
            if(equalsDetected == 0) b += value;
            else b -= value;
            li = li->next;
        }
    }
    if(acceptCharacter(&li, '-')){
        if(acceptIdentifier(&li)){
            if(equalsDetected==0) a--;
            else a++;
        }
        if(li != NULL && li->tt == Number){
            int value = li->t.number;
            if(acceptIdentifier(&li)){
                if(equalsDetected==0) a -= value;
                else a += value;
            } else {
                if(equalsDetected == 0) b -= value;
                else b += value;
                li = li->next;
            }
        }
    }
    if(acceptCharacter(&li, '+')){
        if(acceptIdentifier(&li)){
            if(equalsDetected==0) a++;
            else a--;
        }
        if(li != NULL && li->tt == Number){
            int value = li->t.number;
            if(acceptIdentifier(&li)){
                if(equalsDetected==0) a += value;
                else a -= value;
            } else {
                if(equalsDetected == 0) b += value;
                else b -= value;
                li = li->next;
            }
        }
    }
    x = (double) -b/a;
    return x;
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
