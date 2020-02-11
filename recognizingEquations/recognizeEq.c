#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL */
#include "scanner.h"
#include "recognizeExp.h"
#include "recognizeEq.h"
#include <string.h>

int variableCounter(List li){
    char *str = malloc(100 * sizeof(char));
    int first=1, flag=0, cnt=0;
    while(li != NULL){
        if(li->tt == Identifier && first){
            strcpy(str, li->t.identifier);
            printf("\nstring : %s\n", str);
            first=0;
            cnt++;
            li = li->next;
        }
        if(li->tt == Identifier){
            cnt++;
            flag = strcmp(str, li->t.identifier);   //flag = 0 if they are equal
            if(!flag){
                printf("it gets here\n\n\n\n");
                free(str);
                return 1;
            }
        }
        li = li->next;
    }
    printf("\ncnt=%d\n", cnt);
    if(cnt==1){
        free(str);
        return 0;
    }
    free(str);
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
    printf("the token list is ");
    printList(tl);
    tl1 = tl;
    if (acceptEquations(&tl1) && tl1 == NULL) {
      printf("this is an equation");
      if(variableCounter(tl)){
          printf(", but not in 1 variable\n");
      }
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
