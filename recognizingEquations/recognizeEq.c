#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL */
#include "scanner.h"
#include "recognizeExp.h"
#include "recognizeEq.h"
#include <string.h>

int degree(List li){
    int degree = 0;
    while(li != NULL){
        if(li->tt == Identifier){
            li = li->next;
            if(li == NULL) {
                degree = 1;
                break;
            }
            if(li->tt == Symbol && li->t.symbol == '^'){
                li = li->next;
                if(li == NULL) break;
                if(li->tt == Number && li->t.number > degree) degree = li->t.number;
            }
            else if(degree < 1) degree = 1;
        }
        if(li == NULL) break;
        li = li->next;
    }
    return degree;
}

int variableCounter(List li){
    char *str;
    int first=1, flag=0, cnt=0;
    while(li != NULL){
        if(li->tt == Identifier && first){
            str =  li->t.identifier;
            first=0;
            cnt++;
            if(li == NULL) break;
            li = li->next;
        }
        if(li == NULL) break;
        if(li->tt == Identifier){
            cnt++;
            flag = strcmp(str, li->t.identifier);   //flag = 0 if they are equal
            if(flag != 0){
                return 1;
            }
        }
        if(li == NULL) break;
        li = li->next;
    }
    if(cnt == 0) return 1;
    if(cnt==1){
        return 0;
    }
    return 0;
}

int acceptTermEq(List *lp) {
    List sent = *lp;
  if(acceptNumber(lp) && acceptIdentifier(lp) &&
  acceptCharacter(lp, '^') && acceptNumber(lp)) return 1;
  *lp = sent;
  if(acceptNumber(lp) && acceptIdentifier(lp)) return 1;
  *lp = sent;
  if(acceptIdentifier(lp) && acceptCharacter(lp, '^') && acceptNumber(lp)) return 1;
  *lp = sent;
  if(acceptIdentifier(lp)) return 1;
  *lp = sent;
  if(acceptNumber(lp)) return 1;
  return 0;
}

int acceptExpressionEq(List *lp) {
    if(acceptCharacter(lp, '-')){
        if(!acceptTermEq(lp)) return 0;
    }
  else if (!acceptTermEq(lp)) {
    return 0;
  }
  while (acceptCharacter(lp, '+') || acceptCharacter(lp, '-')) {
    if (!acceptTermEq(lp)) {
      return 0;
    }
  }
  return 1;
}

int acceptEquations(List *lp){
    return (acceptExpressionEq(lp) && acceptCharacter(lp, '=') && acceptExpressionEq(lp));
}

void recognizeEquations() {
  char *ar;
  List tl, tl1;
  printf("give an equation: ");
  ar = readInput();
  while (ar[0] != '!') {
    tl = tokenList(ar);
    // printf("the token list is ");
    printList(tl);
    tl1 = tl;
    if (acceptEquations(&tl1) && tl1 == NULL) {
      printf("this is an equation");
      if(variableCounter(tl)){
          printf(", but not in 1 variable\n");
      }
      else printf(" in 1 variable of degree %d\n", degree(tl));
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
