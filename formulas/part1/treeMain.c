#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"
#include "treeForm.h"

/* Main function to read in user input formulas and convert them into
a logical formula tree composed of nodes for each character. */
int main(int argc, char *argv[]) {
  char *ar;
  List tl, tl1;
  tl1 = NULL;
  printf("give a formula: ");
  /* Create an array for the user input formula */
  ar = readInput();
  while (ar[0] != '!') {
    /* Create a token list from the array, removing spaces and paranthesis */
    tl = tokenList(ar);
    printList(tl);
    tl1 = tl;
    FormTree t = NULL;
    /* If the token list is not NULL and it is possible to create a tree */
    if ( treeBiconditional(&tl1,&t) && tl1 == NULL ) {
      printf("with parentheses: ");
      printTree(t);
      printf("\n");
      int max = 0;
      /* Determine complexity of the tree by calculating the depth of the
      longest branch */
      complexity(t, &max, 0);
      printf("complexity: %d\n", max);
      freeTree(t);
      /* If token list was NULL or this is not a logical formula */
    } else {
      printf("this is not a formula\n");
      if (t != NULL) {
        freeTree(t);
      }
    }
    free(ar);
    freeTokenList(tl);
    /* Ready for the next user input formula */
    printf("\ngive a formula: ");
    ar = readInput();
  }
  /* If a '!' was input, then the program will end */
  free(ar);
  printf("good bye\n");
  return 0;
}
