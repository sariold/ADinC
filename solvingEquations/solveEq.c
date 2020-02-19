#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL */
#include <string.h>
#include <math.h>
#include "scanner.h"
#include "recognizeExp.h"
#include "recognizeEq.h"
#include "solveEq.h"

void solveSystems(List li1, List li2){
    int first = 1, second = 1;
    List copyli1, copyli2;
    char *firstIdentifier, *secondIdentifier;
    copyli1 = li1;
    copyli2 = li2;
    while(copyli1 != NULL){
        if(first && copyli1->tt == Identifier){
            firstIdentifier = copyli1->t.identifier;
            first = 0;
            copyli1 = copyli1->next;
        }
        if(copyli1->tt == Identifier && strcmp(firstIdentifier, copyli1->t.identifier)!=0){
            secondIdentifier = copyli1->t.identifier;
            second = 0;
            break;
            copyli1 = copyli1->next;
        }
        if(copyli1 != NULL) copyli1 = copyli1->next;
    }
    if(second){
        while(copyli2 != NULL){
            if(second && copyli2->tt == Identifier && strcmp(firstIdentifier, copyli2->t.identifier)!=0){
                secondIdentifier = copyli2->t.identifier;
                second = 0;
                break;
                copyli2 = copyli2->next;
            }
            if(copyli2 != NULL) copyli2 = copyli2->next;
        }
    }
    //Two equations, ax + by = c and dx + ey = f
    int a=0,b=0,c=0,d=0,e=0,f=0, equalsDetected=0;
    while(li1 != NULL){
        if(acceptCharacter(&li1, '=')) equalsDetected=1;
        if(li1 != NULL && li1->tt == Identifier){
            if(strcmp(firstIdentifier, li1->t.identifier)==0){
                if(equalsDetected==0) a++;
                else a--;
            }
            if(strcmp(secondIdentifier, li1->t.identifier) == 0){
                if(equalsDetected==0) b++;
                else b--;
            }
            li1 = li1->next;
        }
        if(li1 != NULL && li1)
    }
}



int twoVariableChecker(List li){
    char *str, *str1;
    int first=1, flag=0, cnt=0, second=1, flag1=0, differentVariables=0;
    while(li != NULL){
        if(li->tt == Identifier && first){
            str =  li->t.identifier;
            first=0;
            cnt++;
            li = li->next;
            differentVariables++;
        }
        if(first == 0 && second && li->tt == Identifier && strcmp(str, li->t.identifier) != 0){
            str1 = li->t.identifier;
            second = 0;
            cnt++;
            li = li->next;
            differentVariables++;
        }
        if(li != NULL && li->tt == Identifier){
            cnt++;
            flag = strcmp(str, li->t.identifier);
            flag1 = strcmp(str1, li->t.identifier);
            if(flag != 0 && flag2 != 0) {
                differentVariables++;
                return differentVariables;
            }
        }
        if(li != NULL)  li = li->next;
    }
    return differentVariables;
}

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
    List tl, tl1, tl2, tl3;
    printf("give an equation: ");
    ar = readInput();
    while (ar[0] != '!') {
      tl = tokenList(ar);
      printList(tl);
      tl1 = tl;
      printf("give an equation: ");
      ar = readInput();
      tl2 = tokenList(ar);
      printList(tl2);
      tl3=tl2;
      if (acceptEquations(&tl1) && tl1 == NULL && acceptEquations(&tl3) && tl3 == NULL) {
          if(twoVariableChecker(tl) < 3 && twoVariableChecker(tl2) < 3){

          }
        // // printf("this is an equation");
        // if(variableCounter(tl)){
        //     if(twoVariableChecker(tl)){
        //         solveSystems(tl, tl2);
        //     }
        //     // printf(", but not in 1 variable\n");
        // }
        // else {
        //     // printf(" in 1 variable of degree %d\n", degree(tl));
        //     if(degree(tl) == 1) {
        //         solve(tl);
        //     }
        //     else if(degree(tl) == 2) {
        //         solveQuads(tl);
        //     }
        // }
      }
      // else {
      //   // printf("this is not an equation\n");
      // }
      free(ar);
      freeTokenList(tl);
      freeTokenList(tl2);
      printf("\ngive an equation: ");
      ar = readInput();
    }
    free(ar);
    printf("good bye\n");
}
