/* scanner.h for assignment 4 on logical formulas */

#ifndef SCANNER_H
#define SCANNER_H

#define MAXINPUT 100  /* maximal length of the input */
#define MAXIDENT 10   /* maximal length of an identifier */



/* Declaration of the functions that are defined in scanner.c and to be used outside it. */

char *readInput();
void scanExpressions();

#endif
