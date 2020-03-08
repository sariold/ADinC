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

int acceptCharacter(List *lp, char c) {
  if (*lp != NULL && (*lp)->tt == Symbol && ((*lp)->t).symbol == c ) {
    *lp = (*lp)->next;
    return 1;
  }
  return 0;
}

/* Creates a new form tree node with specific token type, the token itself,
the left tree node it should point to and the right tree node, can be set to
NULL if you do not want additional branches. */
FormTree newFormTreeNode(TokenType tt, Token t, FormTree tL, FormTree tR) {
  FormTree new = malloc(sizeof(FormTreeNode));
  assert (new != NULL);
  new->tt = tt;
  new->t = t;
  new->left = tL;
  new->right = tR;
  return new;
}

/* Recursive free function in order to free all the left and right branches
of a tree and then the tree node itself. */
void freeTree(FormTree t) {
  if (t == NULL) {
    return;
  }
  freeTree(t->left);
  freeTree(t->right);
  free(t);
}

// <identifier> ::= <letter> { <letter> | <digit> }
int treeIdentifier(List *lp, FormTree *t) {
  if (*lp != NULL && (*lp)->tt == Identifier ) {
      /* New tree node with identifier as main node */
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
    /* New tree node with 'T' as main node */
    *t = newFormTreeNode(Symbol, tok, NULL, NULL);
    return 1;
  }
  if (acceptCharacter(lp,'F')) {
    Token tok;
    tok.symbol = 'F';
    /* New tree node with 'F' as main node */
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
/* Due to negation statements having the strongest binding strength,
this function is called last */
int treeLiteral(List *lp, FormTree *t) {
  if (treeAtom(lp,t)) {
    return 1;
  }
  if (acceptCharacter(lp,'~')) {
    FormTree tL = NULL;
    if (treeAtom(lp, &tL)) {
      Token tok;
      tok.symbol = '~';
      /* New tree node with '~' as main node and points to the original left
      node, the right node is null because this is a negation statement */
      *t = newFormTreeNode(Symbol, tok, tL, NULL);
      return 1;
    }
    freeTree(tL);
  }
  return 0;
}

// <formula>  ::=  <literal> { '&' <literal> }
/* Due to conjunction statements having the second strongest binding strength,
this function is called fourth */
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
    /* New tree node with '&' as main node and points to the original left
    and right nodes*/
    *t = newFormTreeNode(Symbol, tok, tL, tR);
  } /* no '&', so we reached the end of conjunction */
  return 1;
}

// <disjunctions> ::= <forumla> {'|' <formula>}
/* Due to disjunction statements having the third weakest binding strength,
this function is called third */
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
        /* New tree node with '|' as main node and points to the original left
        and right nodes*/
        *t = newFormTreeNode(Symbol, tok, tL, tR);
    }
    return 1;
}

/* Due to implication statements having the second weakest binding strength,
this function is called second */
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
                /* New tree node with '-' as main node and points to the
                original left and right nodes*/
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

/* Due to biconditional statements having the weakest binding strength, this
function is called first */
 int treeBiconditional(List *lp, FormTree *t){
     FormTree tL = *t;
     /* Determining if this formula is a implication statement */
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
                 /* New tree node with '<' as main node and points to the
                 original left and right nodes*/
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

/* Recursive function that checks all branches of a tree in order to determine
the longest branch and returns the pointer max with the depth. */
void complexity(FormTree t, int *max, int depth){
    if (t == NULL) return;
    if (depth > *max) *max = depth;
    complexity(t->left, max, depth+1);
    complexity(t->right, max, depth+1);
}

/* Prints the nodes of a tree, outputs them as a logical formula by determing
the logical operator prior to an atom, then prints the proper parantheses
based on the binding strength of each operator. */
void printTree(FormTree t) {
  if (t == NULL) {
    return;
  }
  switch (t->tt) {
  case Symbol:
    switch (t->t.symbol) {
    case 'T':
    case 'F':
      printf("%c",t->t.symbol); // print 'F' or 'T'
      break;
    case '~':
      printf("(~");
      printTree(t->left); // print negated formula
      printf(")");
      break;
    case '-':
      printf("(");
      printTree(t->left); // print first formula
      printf(" -> "); // print implication
      printTree(t->right); // print right formula
      printf(")");
      break;
    case '<':
      printf("(");
      printTree(t->left); // print left formula
      printf(" <-> "); // print biconditional
      printTree(t->right); // print right formula
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
    /* Identifier is a char array, therefore the string must be printed
    instead of a single character as seen in the above cases. */
  case Identifier:
    printf("%s", t->t.identifier);
    break;
  }
}
