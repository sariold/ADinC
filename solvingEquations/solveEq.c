#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL */
#include <string.h>
#include <math.h>
#include "scanner.h"
#include "recognizeExp.h"
#include "recognizeEq.h"
#include "solveEq.h"

void solve(List li){
    double x = 0.0;
    int equalsDetected = 0, a=0, b=0;
// We get an equation in the form ax+b = cx+d, so we restrict it to ex+f=0
    while(li != NULL){
        if(acceptCharacter(&li, '=')) equalsDetected=1;
        if(acceptIdentifier(&li)){
            if(acceptCharacter(&li, '^')){
                if(li->t.number > 0){
                    if(equalsDetected==0) a++;
                    else a--;
                }
                else {
                    if(equalsDetected==0) b++;
                    else b--;
                }
                li = li->next;
            }
            else {
                if(equalsDetected==0) a++;
                else a--;
            }
        }
        if(li != NULL && li->tt == Number){
            int value = li->t.number;
            li = li->next;
            if(acceptIdentifier(&li)){
                if(acceptCharacter(&li, '^')){
                    if(li->t.number > 0){
                        if(equalsDetected==0) a += value;
                        else a -= value;
                    }
                    else {
                        if(equalsDetected==0) b += value;
                        else b -= value;
                    }
                    li=li->next;
                }
                else {
                    if(equalsDetected==0) a += value;
                    else a -= value;
                }
            }
            else {
                if(equalsDetected == 0) b += value;
                else b -= value;
            }
        }
        if(acceptCharacter(&li, '-')){
            if(acceptIdentifier(&li)){
                if(acceptCharacter(&li, '^')){
                    if(li->t.number > 0){
                        if(equalsDetected==0) a--;
                        else a++;
                    }
                    else {
                        if(equalsDetected==0) b--;
                        else b++;
                    }
                    li = li->next;
                }
                else{
                    if(equalsDetected==0) a--;
                    else a++;
                }
            }
            if(li != NULL && li->tt == Number){
                int value = li->t.number;
                li = li->next;
                if(acceptIdentifier(&li)){
                    if(acceptCharacter(&li, '^')){
                        if(li->t.number > 0){
                            if(equalsDetected==0) a-=value;
                            else a+=value;
                        }
                        else {
                            if(equalsDetected==0) b -= value;
                            else b += value;
                        }
                        li=li->next;
                    }
                    else {
                        if(equalsDetected==0) a -= value;
                        else a += value;
                    }
                }
                else {
                    if(equalsDetected == 0) b -= value;
                    else b += value;
                }
            }
        }
        if(acceptCharacter(&li, '+')){
            if(acceptIdentifier(&li)){
                if(acceptCharacter(&li, '^')){
                    if(li->t.number > 0){
                        if(equalsDetected==0) a++;
                        else a--;
                    }
                    else {
                        if(equalsDetected==0) b++;
                        else b--;
                    }
                    li = li->next;
                }
                else {
                    if(equalsDetected==0) a++;
                    else a--;
                }
            }
            if(li != NULL && li->tt == Number){
                int value = li->t.number;
                li = li->next;
                if(acceptIdentifier(&li)){
                    if(acceptCharacter(&li, '^')){
                        if(li->t.number > 0){
                            if(equalsDetected==0) a+=value;
                            else a-=value;
                        }
                        else {
                            if(equalsDetected==0) b += value;
                            else b-=value;
                        }
                        li = li->next;
                    }
                    else {
                        if(equalsDetected==0) a += value;
                        else a -= value;
                    }
                }
                else {
                    if(equalsDetected == 0) b += value;
                    else b -= value;
                }
            }
        }
    }
    x = (double)(-b)/a;
    if(a == 0) {
        printf("not solvable\n");
        return;
    }
    else if(x >= -0.0005 && x <= 0.0000){
        printf("solution: 0.000\n");
    }
    else printf("solution: %.3lf\n", x);
}

void solveQuads(List li){
    double x = 0.0;
    double y = 0.0;
    int equalsDetected = 0, a=0, b=0, c=0;
// We get an equation in the form ax+b = cx+d, so we restrict it to ex+f=0
    while(li != NULL){
        if(acceptCharacter(&li, '=')) equalsDetected=1;
        if(acceptIdentifier(&li)){
            if(acceptCharacter(&li, '^')){
                if(li->t.number == 2){
                    if(equalsDetected==0) a++;
                    else a--;
                }
                else if(li->t.number == 1){
                    if(equalsDetected==0) b++;
                    else b--;
                }
                else {
                    if(equalsDetected==0) c++;
                    else c--;
                }
                li = li->next;
            }
            else {
                if(equalsDetected==0) b++;
                else b--;
            }
        }
        if(li != NULL && li->tt == Number){
            int value = li->t.number;
            li = li->next;
            if(acceptIdentifier(&li)){
                if(acceptCharacter(&li, '^')){
                    if(li->t.number == 2){
                        if(equalsDetected==0) a += value;
                        else a -= value;
                    }
                    else if(li->t.number == 1){
                        if(equalsDetected==0) b += value;
                        else b -= value;
                    }
                    else {
                        if(equalsDetected==0) c += value;
                        else c -= value;
                    }
                    li=li->next;
                }
                else {
                    if(equalsDetected==0) b += value;
                    else b -= value;
                }
            }
            else {
                if(equalsDetected == 0) c += value;
                else c -= value;
            }
        }
        if(acceptCharacter(&li, '-')){
            if(acceptIdentifier(&li)){
                if(acceptCharacter(&li, '^')){
                    if(li->t.number == 2){
                        if(equalsDetected==0) a--;
                        else a++;
                    }
                    else if(li->t.number == 1){
                        if(equalsDetected==0) b--;
                        else b++;
                    }
                    else {
                        if(equalsDetected==0) c--;
                        else c++;
                    }
                    li = li->next;
                }
                else{
                    if(equalsDetected==0) b--;
                    else b++;
                }
            }
            if(li != NULL && li->tt == Number){
                int value = li->t.number;
                li = li->next;
                if(acceptIdentifier(&li)){
                    if(acceptCharacter(&li, '^')){
                        if(li->t.number == 2){
                            if(equalsDetected==0) a-=value;
                            else a+=value;
                        }
                        else if(li->t.number == 1){
                            if(equalsDetected==0) b-=value;
                            else b+=value;
                        }
                        else {
                            if(equalsDetected==0) c -= value;
                            else c += value;
                        }
                        li=li->next;
                    }
                    else {
                        if(equalsDetected==0) b -= value;
                        else b += value;
                    }
                }
                else {
                    if(equalsDetected == 0) c -= value;
                    else c += value;
                }
            }
        }
        if(acceptCharacter(&li, '+')){
            if(acceptIdentifier(&li)){
                if(acceptCharacter(&li, '^')){
                    if(li->t.number == 2){
                        if(equalsDetected==0) a++;
                        else a--;
                    }
                    else if(li->t.number == 1){
                        if(equalsDetected==0) b++;
                        else b--;
                    }
                    else {
                        if(equalsDetected==0) c++;
                        else c--;
                    }
                    li = li->next;
                }
                else {
                    if(equalsDetected==0) b++;
                    else b--;
                }
            }
            if(li != NULL && li->tt == Number){
                int value = li->t.number;
                li = li->next;
                if(acceptIdentifier(&li)){
                    if(acceptCharacter(&li, '^')){
                        if(li->t.number == 2){
                            if(equalsDetected==0) a+=value;
                            else a-=value;
                        }
                        else if(li->t.number == 1){
                            if(equalsDetected==0) b+=value;
                            else b-=value;
                        }
                        else {
                            if(equalsDetected==0) c += value;
                            else c-=value;
                        }
                        li = li->next;
                    }
                    else {
                        if(equalsDetected==0) b += value;
                        else b -= value;
                    }
                }
                else {
                    if(equalsDetected == 0) c += value;
                    else c -= value;
                }
            }
        }
    }

    double disc = ((b * b) - (4 * a * c));
    if(disc < 0) {
        printf("not solvable\n");
        return;
    }
    if(a == 0){
        printf("solution: %.3lf\n", (double)-c/b);
        return;
    }
    double squared = sqrt(disc);
    x = (double) (-b + squared)/(2 * a);
    y = (double) (-b - squared)/(2 * a);
    if(x == y) {
        printf("solution: %.3lf\n", x);
        return;
    }
    else if(x >= -0.0005 && x <= 0.0000) x = 0.000;
    else if(y >= -0.0005 && y <= 0.0000) y = 0.000;
    printf("solution: %.3lf and %.3lf\n", x, y);
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
        else {
            printf(" in 1 variable of degree %d\n", degree(tl));
            if(degree(tl) == 1) {
                solve(tl);
            }
            else if(degree(tl) == 2) {
                solveQuads(tl);
            }
        }
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
