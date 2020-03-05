/* treeForm.c for assignment 4 on logical formulas
 *
 * This recognizes and makes syntax trees for the following grammar:
 *
 * <atom>     ::=  'T' | 'F' | <identifier> | '(' <formula> ')'
 * <literal>  ::=  <atom> | '~' <atom>
 * <formula>  ::=  <literal> { '&' <literal> }
 * <conjunctions> ::= <forumla> {'|' <formula>}
 * <implication> ::= <conjunction> ['->' <conjunction>]
 * <biconditional> ::= <implication> ['<->' <implication>].
 */

#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL */
#include <assert.h>

#include "scanner.h"
#include "treeForm.h"

/* The acceptCharacter function takes a pointer to a token list and a character.
 * It checks whether the first token in the list is a Symbol with the given character.
 * When that is the case, it returns 1 and moves the pointer to the rest of the token list.
 * Otherwise it yields 0 and the pointer remains unchanged.
 */

FormTree copyTree(FormTree t){
    if(t == NULL) return t;
    return newFormTreeNode(t->tt, t->t, t->left, t->right);
}

void translate (FormTree *t){
    if(*t == NULL) return;
    if((*t)->tt == Symbol && (*t)->t.symbol == '|'){
        Token tok;
        tok.symbol = '~';
        FormTree t1 = newFormTreeNode(Symbol, tok, (*t)->left, NULL);
        FormTree t2 = newFormTreeNode(Symbol, tok, (*t)->right, NULL);
        tok.symbol = '&';
        FormTree t3 = newFormTreeNode(Symbol, tok, t1, t2);
        tok.symbol = '~';
        free(*t);
        *t = newFormTreeNode(Symbol, tok, t3, NULL);
        return;
    }
    if((*t)->tt == Symbol && (*t)->t.symbol == '-'){
        Token tok;
        tok.symbol = '~';
        FormTree t1 = newFormTreeNode(Symbol, tok, (*t)->left, NULL);
        tok.symbol = '|';
        FormTree t2 = (*t)->right;
        free(*t);
        *t = newFormTreeNode(Symbol, tok, t1, t2);
        translate(t);
    }
    if((*t)->tt == Symbol && (*t)->t.symbol == '<'){
        Token tokAnd, tokOr, tokNeg;
        tokAnd.symbol = '&';
        tokOr.symbol = '|';
        tokNeg.symbol = '~';
        FormTree t1 = copyTree((*t)->left);
        FormTree t2 =  copyTree((*t)->right);
        FormTree translatedLeft = newFormTreeNode(Symbol, tokAnd, t1, t2);
        FormTree t3 = copyTree((*t)->left);
        FormTree t4 = copyTree((*t)->right);
        FormTree translatedRight = newFormTreeNode(Symbol, tokAnd,
            newFormTreeNode(Symbol, tokNeg, t3, NULL),
            newFormTreeNode(Symbol, tokNeg, t4, NULL));
        freeTree(*t);
        *t = newFormTreeNode(Symbol, tokOr, translatedLeft, translatedRight);
        translate(t);
    }
    translate(&((*t)->left));
    translate(&((*t)->right));
}


 void simplify(FormTree *t){
     if(*t == NULL) return;
     simplify(&((*t)->left));
     simplify(&((*t)->right));
     if((*t)->tt == Symbol && (*t)->t.symbol == '-'){
         if(((*t)->left)->tt == Symbol && ((*t)->left)->t.symbol == 'T'){
             FormTree t1 = *t;
             *t = (*t)->right;
             freeTree(t1->left);
             free(t1);
             return;
         }
         if(((*t)->left)->tt == Symbol && ((*t)->left)->t.symbol == 'F'){
             Token tok;
             tok.symbol = 'T';
             freeTree(*t);
             *t = newFormTreeNode(Symbol, tok, NULL, NULL);
             return;
         }
         if(((*t)->right)->tt == Symbol && ((*t)->right)->t.symbol == 'T'){
             Token tok;
             tok.symbol = 'T';
             freeTree(*t);
             *t = newFormTreeNode(Symbol, tok, NULL, NULL);
             return;
         }
         if(((*t)->right)->tt == Symbol && ((*t)->right)->t.symbol == 'F'){
             FormTree t1 = *t;
             Token tok;
             tok.symbol = '~';
             *t = newFormTreeNode(Symbol, tok, t1->left, NULL);
             freeTree(t1->right);
             free(t1);
             return;
         }
     }
     if((*t)->tt == Symbol && (*t)->t.symbol == '<'){
         if(((*t)->right)->tt == Symbol && ((*t)->right)->t.symbol == 'T'){
             FormTree t1 = *t;
             *t = (*t)->left;
             freeTree(t1->right);
             free(t1);
             return;
         }
         if(((*t)->left)->tt == Symbol && ((*t)->left)->t.symbol == 'T'){
             FormTree t1 = *t;
             *t = (*t)->right;
             freeTree(t1->left);
             free(t1);
             return;
         }
     }
     if((*t)->tt == Symbol && (*t)->t.symbol == '~'){
         if(((*t)->left)->tt == Symbol && ((*t)->left)->t.symbol == '~'){
             FormTree t1 = *t;
             *t = ((*t)->left)->left;
             free(t1->left);
             free(t1);
             return;
         }
         if(((*t)->left)->tt == Symbol && ((*t)->left)->t.symbol == 'T'){
             Token tok;
             tok.symbol = 'F';
             freeTree(*t);
             *t = newFormTreeNode(Symbol, tok, NULL, NULL);
             return;
         }
         if(((*t)->left)->tt == Symbol && ((*t)->left)->t.symbol == 'F'){
             Token tok;
             tok.symbol = 'T';
             freeTree(*t);
             *t = newFormTreeNode(Symbol, tok, NULL, NULL);
             return;
         }
     }
     if((*t)->tt == Symbol && (*t)->t.symbol == '|'){
         if((((*t)->left)->tt == Symbol && ((*t)->left)->t.symbol == 'T') ||
         (((*t)->right)->tt == Symbol && ((*t)->right)->t.symbol == 'T')) {
             Token tok;
             tok.symbol = 'T';
             freeTree(*t);
             *t = newFormTreeNode(Symbol, tok, NULL, NULL);
             return;
         }
         if(((*t)->left)->tt == Symbol && ((*t)->left)->t.symbol == 'F') {
             FormTree t1 = *t;
             *t = (*t)->right;
             freeTree(t1->left);
             free(t1);
             return;
         }
         if(((*t)->right)->tt == Symbol && ((*t)->right)->t.symbol == 'F') {
             FormTree t1 = *t;
             *t = (*t)->left;
             freeTree(t1->right);
             free(t1);
             return;
         }
     }
     if((*t)->tt == Symbol && (*t)->t.symbol == '&'){
         if(((*t)->left)->tt == Symbol && ((*t)->left)->t.symbol == 'T') {
             FormTree t1 = *t;
             *t = (*t)->right;
             freeTree(t1->left);
             free(t1);
             return;
         }
         if(((*t)->right)->tt == Symbol && ((*t)->right)->t.symbol == 'T') {
             FormTree t1 = *t;
             *t = (*t)->left;
             freeTree(t1->right);
             free(t1);
             return;
         }
         if((((*t)->left)->tt == Symbol && ((*t)->left)->t.symbol == 'F') ||
         (((*t)->right)->tt == Symbol && ((*t)->right)->t.symbol == 'F')) {
             Token tok;
             tok.symbol = 'F';
             freeTree(*t);
             *t = newFormTreeNode(Symbol, tok, NULL, NULL);
             return;
         }
     }
 }

int acceptCharacter(List *lp, char c) {
  if (*lp != NULL && (*lp)->tt == Symbol && ((*lp)->t).symbol == c ) {
    *lp = (*lp)->next;
    return 1;
  }
  return 0;
}

FormTree newFormTreeNode(TokenType tt, Token t, FormTree tL, FormTree tR) {
  FormTree new = malloc(sizeof(FormTreeNode));
  assert (new != NULL);
  new->tt = tt;
  new->t = t;
  new->left = tL;
  new->right = tR;
  return new;
}

void freeTree(FormTree t) {
  if (t == NULL) {
    return;
  }
  freeTree(t->left);
  freeTree(t->right);
  free(t);
}

int treeIdentifier(List *lp, FormTree *t) {
  if (*lp != NULL && (*lp)->tt == Identifier ) {
    *t = newFormTreeNode(Identifier, (*lp)->t, NULL, NULL);
    *lp = (*lp)->next;
    return 1;
  }
  return 0;
}

// <atom>  ::=  'T' | 'F' | <identifier> | '(' <formula> ')'
int treeAtom(List *lp, FormTree *t) {
  if (acceptCharacter(lp,'T')) {
    Token tok;
    tok.symbol = 'T';
    *t = newFormTreeNode(Symbol, tok, NULL, NULL);
    return 1;
  }
  if (acceptCharacter(lp,'F')) {
    Token tok;
    tok.symbol = 'F';
    *t = newFormTreeNode(Symbol, tok, NULL, NULL);
    return 1;
  }
  if (treeIdentifier(lp,t)) {
    return 1;
  }
  if (acceptCharacter(lp,'(') && treeBiconditional(lp,t) && acceptCharacter(lp,')') ) {
    return 1;
  }
  return 0;
}

// <literal>  ::=  <atom> | '~' <atom>
int treeLiteral(List *lp, FormTree *t) {
  if (treeAtom(lp,t)) {
    return 1;
  }
  if (acceptCharacter(lp,'~')) {
    FormTree tL = NULL;
    if (treeAtom(lp, &tL)) {
      Token tok;
      tok.symbol = '~';
      *t = newFormTreeNode(Symbol, tok, tL, NULL);
      return 1;
    }
    freeTree(tL);
  }
  return 0;
}

// <formula>  ::=  <literal> { '&' <literal> }
int treeFormula(List *lp, FormTree *t) {
  if ( !treeLiteral(lp,t) ) {
    return 0;
  }
  while ( acceptCharacter(lp,'&') ) {
    FormTree tL = *t;
    FormTree tR = NULL;
    if ( !treeLiteral(lp,&tR) ) {
      freeTree(tR);
      return 0;
    }
    Token tok;
    tok.symbol = '&';
    *t = newFormTreeNode(Symbol, tok, tL, tR);
  } /* no '&', so we reached the end of conjunction */
  return 1;
}
// <conjunctions> ::= <forumla> {'|' <formula>}
int treeConjunction(List *lp, FormTree *t){
    if(!treeFormula(lp, t)){
        return 0;
    }
    while(acceptCharacter(lp, '|')){
        FormTree tL = *t;
        FormTree tR = NULL;
        if(!treeFormula(lp, &tR)){
            freeTree(tR);
            return 0;
        }
        Token tok;
        tok.symbol = '|';
        *t = newFormTreeNode(Symbol, tok, tL, tR);
    }
    return 1;
}

int treeImplication(List *lp, FormTree *t){
    FormTree tL = *t;
    if(treeConjunction(lp, &tL)){
        if(acceptCharacter(lp, '-')){
            if(!acceptCharacter(lp, '>')){
                freeTree(tL);
                return 0;
            }
            FormTree tR = NULL;
            if(treeConjunction(lp, &tR)){
                Token tok;
                tok.symbol = '-';
                *t = newFormTreeNode(Symbol, tok, tL, tR);
                return 1;
            }
            else {
                freeTree(tL);
                freeTree(tR);
                return 0;
            }
        }
        *t = tL;
        return 1;
    }
    freeTree(tL);
    return 0;
}

 int treeBiconditional(List *lp, FormTree *t){
     FormTree tL = *t;
     if(treeImplication(lp, &tL)){
         if(acceptCharacter(lp, '<')){
             if(!acceptCharacter(lp, '-')){
                 freeTree(tL);
                 return 0;
             }
             if(!acceptCharacter(lp, '>')){
                 freeTree(tL);
                 return 0;
             }
             FormTree tR = NULL;
             if(treeImplication(lp, &tR)){
                 Token tok;
                 tok.symbol = '<';
                 *t = newFormTreeNode(Symbol, tok, tL, tR);
                 return 1;
             }
             else {
                 freeTree(tL);
                 freeTree(tR);
                 return 0;
             }
         }
         *t = tL;
         return 1;
     }
     freeTree(tL);
     return 0;
 }

void complexity(FormTree t, int *max, int depth){
    if (t == NULL) return;
    if (depth > *max) *max = depth;
    complexity(t->left, max, depth+1);
    complexity(t->right, max, depth+1);
}


void printTree(FormTree t) {
  if (t == NULL) {
    return;
  }
  switch (t->tt) {
  case Symbol:
    switch (t->t.symbol) {
    case 'T':
    case 'F':
      printf("%c",t->t.symbol);
      break;
    case '~':
      printf("(~");
      printTree(t->left);
      printf(")");
      break;
    case '-':
      printf("(");
      printTree(t->left);
      printf(" -> ");
      printTree(t->right);
      printf(")");
      break;
    case '<':
      printf("(");
      printTree(t->left);
      printf(" <-> ");
      printTree(t->right);
      printf(")");
      break;
    default:
      printf("(");
      printTree(t->left);
      printf(" %c ",t->t.symbol);
      printTree(t->right);
      printf(")");
      break;
    }
    break;
  case Identifier:
    printf("%s", t->t.identifier);
    break;
  }
}
