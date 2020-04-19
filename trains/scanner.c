#include <stdio.h>  /* getchar, printf */
#include <stdlib.h> /* NULL, malloc, free */
#include <string.h> /* strcpy */
#include <assert.h> /* assert */
#include "scanner.h"

char *readInput() {
    int strLen = MAXINPUT;
    int c = getchar();
    int i = 0;
    char *s = malloc((strLen+1)*sizeof(char));
    assert( s != NULL );
    while ( c != '\n' ) {
        s[i] = c;
        i++;
        if ( i >= strLen ) {
            strLen = 2*strLen;
            s = realloc(s,(strLen+1)*sizeof(char));
            assert( s != NULL );
        }
        c = getchar();
    }
    s[i] = '\0';
    return s;
}
