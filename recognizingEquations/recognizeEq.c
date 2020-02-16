#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"
#include <string.h>
#include "recognizeExp.h"
#include "recognizeEq.h"

/* Function to determine the highest degree of a given equation */
int degree(List li){
    int degree = 0;
    while(li != NULL){
        if(acceptIdentifier(&li)){
            if(acceptCharacter(&li, '^')){
                /* If the number found following the '^' is the new max, then
                degree is set to this new value */
                if(li->t.number > degree) degree = li->t.number;
            }
            else if(degree < 1) degree = 1;
        }
        if(li != NULL) li = li->next;
    }
    /* If no new max is found, then the degree of the equation is 1 */
    return degree;
}

/* Function to determine how many variables the entire equation contains */
int variableCounter(List li){
    char *str;
    int first = 1, flag = 0, cnt = 0;
    while(li != NULL){
        /* If no identifiers have been found yet, first is set to 0 */
        if(li->tt == Identifier && first){
            /* Set str variable to first indentifier */
            str =  li->t.identifier;
            first=0;
            cnt++;
            li = li->next;
        }
        /* If first is set to 1, meaning first identifier has been found and
        stored */
        if(li != NULL && li->tt == Identifier){
            cnt++;
            /* Flag is set to 0 if both identifiers are the same */
            flag = strcmp(str, li->t.identifier);
            if(flag != 0){
                /* Encountered a different identifier */
                return 1;
            }
        }
        if(li != NULL)  li = li->next;
    }
    /* If 1 is returned then there were more than 1 identifiers */
    return (cnt == 0 ? 1 : 0);
}

/* If branches to determine what kind of grammar composed expression is next on
the token list */
int acceptTermEq(List *lp) {
    /* If the first term is a natural number */
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
    /* If the first term is an identifier */
    if(acceptIdentifier(lp)) {
        if(acceptCharacter(lp, '^')) {
            if(acceptNumber(lp)) return 1;
            else return 0;
        }
        return 1;
    }
    /* Return 0 whenever there is improper grammar terms */
    return 0;
}

/* Function to determine if the current token list is an expression */
int acceptExpressionEq(List *lp) {
    /* Checking for negative terms */
    if(acceptCharacter(lp, '-')){
        if(!acceptTermEq(lp)) return 0;
    }
  else if (!acceptTermEq(lp)) {
    return 0;
  }
  /* Checking for + or - characters as these simple expression do not contain
  multiplication or division */
  while (acceptCharacter(lp, '+') || acceptCharacter(lp, '-')) {
    if (!acceptTermEq(lp)) {
      return 0;
    }
  }
  return 1;
}

/* Equation is made up of a valid expression, an equals character, and another
valid expression */
int acceptEquations(List *lp){
    return (acceptExpressionEq(lp) && acceptCharacter(lp, '=')
    && acceptExpressionEq(lp));
}

/* Same function from Themis given files, with slight changes when determining
both the degree and variable count of a valid equation */
void recognizeEquations() {
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
      /* If variableCounter returns a number greater than 0, then this equation
      contains more than one variable */
      if(variableCounter(tl)){
          printf(", but not in 1 variable\n");
      }
      /* If this equation contains only one variable, then the degree function
      is called to determine the maximum degree of said variable */
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
