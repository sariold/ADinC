#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL */
#include <string.h>
#include "scanner.h"
#include "recognizeExp.h"
#include "recognizeEq.h"
#include "solveEq.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <math.h>
#include "scanner.h"
#include "recognizeExp.h"
#include "recognizeEq.h"
#include "solveEq.h"

void solve(List li){
    double x = 0.0;
    int equalsDetected = 0, a=0, b=0;
    /* *We get an equation in the form ax+b = cx+d, so we restrict it to
    ax + b = 0 */
    while(li != NULL){
        /* Flag to determine if we are reading left or right expression */
        if(acceptCharacter(&li, '=')) equalsDetected=1;
        /* Identifier first */
        if(acceptIdentifier(&li)){
            if(acceptCharacter(&li, '^')){
                if(li->t.number > 0){
                    /* Change value of a depending on which expression is
                    read */
                    if(equalsDetected==0) a++;
                    else a--;
                }
                else {
                    /* x^0 = 1 so the value of b is changed */
                    if(equalsDetected==0) b++;
                    else b--;
                }
                li = li->next;
            }
            else {
                /* Modify value of a if only an identifier is found */
                if(equalsDetected==0) a++;
                else a--;
            }
        }
        /* Number first */
        if(li != NULL && li->tt == Number){
            int value = li->t.number;
            li = li->next;
            /* Identifier following immediately */
            if(acceptIdentifier(&li)){
                if(acceptCharacter(&li, '^')){
                    if(li->t.number > 0){
                        /* Modify value of a depending on the value of ax */
                        if(equalsDetected==0) a += value;
                        else a -= value;
                    }
                    else {
                        /* ax^0 = a so modify the value of b */
                        if(equalsDetected==0) b += value;
                        else b -= value;
                    }
                    li=li->next;
                }
                else {
                    /* ax means modify a */
                    if(equalsDetected==0) a += value;
                    else a -= value;
                }
            }
            else {
                /* Number followed by no identifier means modify b */
                if(equalsDetected == 0) b += value;
                else b -= value;
            }
        }
        /* If first character is a '-' character */
        if(acceptCharacter(&li, '-')){
            /* Followed by an identifier */
            if(acceptIdentifier(&li)){
                if(acceptCharacter(&li, '^')){
                    if(li->t.number > 0){
                        /* x^1 means modify a */
                        if(equalsDetected==0) a--;
                        else a++;
                    }
                    else {
                        /* x^0 means modify b */
                        if(equalsDetected==0) b--;
                        else b++;
                    }
                    li = li->next;
                }
                else{
                    /* An identifier raised to no power means to modify a */
                    if(equalsDetected==0) a--;
                    else a++;
                }
            }
            /* Followed by a natural number */
            if(li != NULL && li->tt == Number){
                int value = li->t.number;
                li = li->next;
                /* Identifier follows */
                if(acceptIdentifier(&li)){
                    if(acceptCharacter(&li, '^')){
                        if(li->t.number > 0){
                            /* ax^1 means modify the value of a */
                            if(equalsDetected==0) a-=value;
                            else a+=value;
                        }
                        else {
                            /* ax^0 means modify b by the value a */
                            if(equalsDetected==0) b -= value;
                            else b += value;
                        }
                        li=li->next;
                    }
                    else {
                        /* Modify the value of a from ax */
                        if(equalsDetected==0) a -= value;
                        else a += value;
                    }
                }
                else {
                    /* Modify the value of b as there is no identifier */
                    if(equalsDetected == 0) b -= value;
                    else b += value;
                }
            }
        }
        /* If the first character is a '+' */
        if(acceptCharacter(&li, '+')){
            /* Identifier follows */
            if(acceptIdentifier(&li)){
                if(acceptCharacter(&li, '^')){
                    /* ax^1 means modify the value of a */
                    if(li->t.number > 0){
                        if(equalsDetected==0) a++;
                        else a--;
                    }
                    else {
                        /* ax^0 means modify the value of b */
                        if(equalsDetected==0) b++;
                        else b--;
                    }
                    li = li->next;
                }
                else {
                    /* A single modifier means modify the value of a */
                    if(equalsDetected==0) a++;
                    else a--;
                }
            }
            /* Natural number follows */
            if(li != NULL && li->tt == Number){
                int value = li->t.number;
                li = li->next;
                /* Indentifier follows the natural number */
                if(acceptIdentifier(&li)){
                    if(acceptCharacter(&li, '^')){
                        if(li->t.number > 0){
                            /* ax^1 means modify the value of a */
                            if(equalsDetected==0) a+=value;
                            else a-=value;
                        }
                        else {
                            /* ax^0 means modify the value of b */
                            if(equalsDetected==0) b += value;
                            else b-=value;
                        }
                        li = li->next;
                    }
                    else {
                        /* ax means modify the value of a */
                        if(equalsDetected==0) a += value;
                        else a -= value;
                    }
                }
                else {
                    /* A number followed by no identifier means modify b */
                    if(equalsDetected == 0) b += value;
                    else b -= value;
                }
            }
        }
    }
    /* Calculating x can be done by taking -b/a */
    x = (double)(-b)/a;
    if(a == 0) {
        /* Division by 0 is undefined */
        printf("not solvable\n");
        return;
    }
    /* C has tendency to print -0.000 so this sets a range of values to 0 */
    else if(x >= -0.0005 && x <= 0.0000){
        printf("solution: 0.000\n");
    }
    /* Print 3 placeholders after the decimal */
    else printf("solution: %.3lf\n", x);
}

// void solveQuads(List li){
//     double x = 0.0;
//     double y = 0.0;
//     int equalsDetected = 0, a=0, b=0, c=0;
//     while(li != NULL){
//         /* Flag to determine if reading left or right expression  */
//         if(acceptCharacter(&li, '=')) equalsDetected=1;
//         /* Identifier first */
//         if(acceptIdentifier(&li)){
//             if(acceptCharacter(&li, '^')){
//                 /* Identifier to the power 2 means modify a */
//                 if(li->t.number == 2){
//                     if(equalsDetected==0) a++;
//                     else a--;
//                 }
//                 /* Identifier to the power 1 means modify b */
//                 else if(li->t.number == 1){
//                     if(equalsDetected==0) b++;
//                     else b--;
//                 }
//                 /* Identifier to the power 0 means modify c */
//                 else {
//                     if(equalsDetected==0) c++;
//                     else c--;
//                 }
//                 li = li->next;
//             }
//             /* Single identifier means modify value b */
//             else {
//                 if(equalsDetected==0) b++;
//                 else b--;
//             }
//         }
//         /* Natural number first */
//         if(li != NULL && li->tt == Number){
//             int value = li->t.number;
//             li = li->next;
//             /* Followed by an identifier */
//             if(acceptIdentifier(&li)){
//                 if(acceptCharacter(&li, '^')){
//                     /* Identifier to the power 2 means modify a */
//                     if(li->t.number == 2){
//                         if(equalsDetected==0) a += value;
//                         else a -= value;
//                     }
//                     /* Identifier to the power 1 means modify b */
//                     else if(li->t.number == 1){
//                         if(equalsDetected==0) b += value;
//                         else b -= value;
//                     }
//                     /* Identifier to the power 0 means modify c */
//                     else {
//                         if(equalsDetected==0) c += value;
//                         else c -= value;
//                     }
//                     li=li->next;
//                 }
//                 /* Identifier with no power means modify b */
//                 else {
//                     if(equalsDetected==0) b += value;
//                     else b -= value;
//                 }
//             }
//             /* Number followed by no identifier means modify c */
//             else {
//                 if(equalsDetected == 0) c += value;
//                 else c -= value;
//             }
//         }
//         /* Next character is a '-' sign */
//         if(acceptCharacter(&li, '-')){
//             /* Followed by an Identifier */
//             if(acceptIdentifier(&li)){
//                 if(acceptCharacter(&li, '^')){
//                     /* Identifier to the power 2 means modify a */
//                     if(li->t.number == 2){
//                         if(equalsDetected==0) a--;
//                         else a++;
//                     }
//                     /* Identifier to the power 1 means modify b */
//                     else if(li->t.number == 1){
//                         if(equalsDetected==0) b--;
//                         else b++;
//                     }
//                     /* Identifier to the power 0 means modify c */
//                     else {
//                         if(equalsDetected==0) c--;
//                         else c++;
//                     }
//                     li = li->next;
//                 }
//                 /* Single identifier means modify b */
//                 else{
//                     if(equalsDetected==0) b--;
//                     else b++;
//                 }
//             }
//             /* Followed by a natural number */
//             if(li != NULL && li->tt == Number){
//                 int value = li->t.number;
//                 li = li->next;
//                 /* Followed by an identifier */
//                 if(acceptIdentifier(&li)){
//                     if(acceptCharacter(&li, '^')){
//                         /* Identifier to the power 2 means modify a */
//                         if(li->t.number == 2){
//                             if(equalsDetected==0) a-=value;
//                             else a+=value;
//                         }
//                         /* Identifier to the power 1 means modify b */
//                         else if(li->t.number == 1){
//                             if(equalsDetected==0) b-=value;
//                             else b+=value;
//                         }
//                         /* Identifier to the power 0 means modify c */
//                         else {
//                             if(equalsDetected==0) c -= value;
//                             else c += value;
//                         }
//                         li=li->next;
//                     }
//                     /* Natural number followed by identifier with no power
//                     means modify value b */
//                     else {
//                         if(equalsDetected==0) b -= value;
//                         else b += value;
//                     }
//                 }
//                 /* Natural number with no identifier means modify c */
//                 else {
//                     if(equalsDetected == 0) c -= value;
//                     else c += value;
//                 }
//             }
//         }
//         /* Next character is a '+' sign */
//         if(acceptCharacter(&li, '+')){
//             /* Identifier first */
//             if(acceptIdentifier(&li)){
//                 if(acceptCharacter(&li, '^')){
//                     /* Identifier to the power 2 means modify a */
//                     if(li->t.number == 2){
//                         if(equalsDetected==0) a++;
//                         else a--;
//                     }
//                     /* Identifier to the power 1 means modify b */
//                     else if(li->t.number == 1){
//                         if(equalsDetected==0) b++;
//                         else b--;
//                     }
//                     /* Identifier to the power 0 means modify c */
//                     else {
//                         if(equalsDetected==0) c++;
//                         else c--;
//                     }
//                     li = li->next;
//                 }
//                 /* Single identifier means modify b */
//                 else {
//                     if(equalsDetected==0) b++;
//                     else b--;
//                 }
//             }
//             /* Natural number first */
//             if(li != NULL && li->tt == Number){
//                 int value = li->t.number;
//                 li = li->next;
//                 /* Followed by an identifier */
//                 if(acceptIdentifier(&li)){
//                     if(acceptCharacter(&li, '^')){
//                         /* Identifier to the power 2 means modify a */
//                         if(li->t.number == 2){
//                             if(equalsDetected==0) a+=value;
//                             else a-=value;
//                         }
//                         /* Identifier to the power 1 means modify b */
//                         else if(li->t.number == 1){
//                             if(equalsDetected==0) b+=value;
//                             else b-=value;
//                         }
//                         /* Identifier to the power 0 means modify c */
//                         else {
//                             if(equalsDetected==0) c += value;
//                             else c-=value;
//                         }
//                         li = li->next;
//                     }
//                     /* Identifier to no power  means modify b */
//                     else {
//                         if(equalsDetected==0) b += value;
//                         else b -= value;
//                     }
//                 }
//                 /* number followed by no identifier means modify c */
//                 else {
//                     if(equalsDetected == 0) c += value;
//                     else c -= value;
//                 }
//             }
//         }
//     }
//     /* Determining the discrimant of this quadratic function */
//     double disc = ((b * b) - (4 * a * c));
//     /* Discrimant less than 0 results in a not solvable due to imaginary
//     solutions */
//     if(disc < 0) {
//         printf("not solvable\n");
//         return;
//     }
//     /* If a is 0 then 0x^2 means this is a linear equation of degree 1 */
//     if(a == 0){
//         printf("solution: %.3lf\n", (double)-c/b);
//         return;
//     }
//     double squared = sqrt(disc);
//     x = (double) (-b + squared)/(2 * a);
//     y = (double) (-b - squared)/(2 * a);
//     /* Print out one solution */
//     if(x == y) {
//         printf("solution: %.3lf\n", x);
//         return;
//     }
//     /* Rounding fix to account for printing -0.000 */
//     else if(x >= -0.0005 && x <= 0.0000) x = 0.000;
//     else if(y >= -0.0005 && y <= 0.0000) y = 0.000;
//     printf("solution: %.3lf and %.3lf\n", x, y);
// }

/* Function that tokenizes the user input and then checks if the token list is
an acceptable equation */
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
        /* If variableCounter returns a value higher than 0, then this equation
        contains more than 1 variable */
        if(variableCounter(tl)){
            printf(", but not in 1 variable\n");
        }
        else {
            printf(" in 1 variable of degree %d\n", degree(tl));
            /* If the degree of the equation is 1, then the linear solve
            function is called */
            if(degree(tl) == 1) {
                solve(tl);
            }
            /* If equation is of degree 2, then the quadratic solve function
            is called */
            // else if(degree(tl) == 2) {
            //     solveQuads(tl);
            // }
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
