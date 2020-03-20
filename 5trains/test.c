#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

char *readInput() {
  int strLen = 30;
  int c = getchar();
  int i = 0;
  char *s = malloc((strLen+1)*sizeof(char));
  assert( s != NULL );
  while ( c != '\n' ) {
    s[i] = c;
    i++;
    if ( i >= strLen ) { /* s is not large enough, its length is doubled */
      strLen = 2*strLen;
      s = realloc(s,(strLen+1)*sizeof(char));
      assert( s != NULL );
    }
    c = getchar();
  }
  s[i] = '\0';
  return s;
}

int cityToId(char *s){
    char amsterdam[10] = "Amsterdam";
    char haag[9] = "Den Haag";
    char eindhoven[10] = "Eindhoven";
    char utrecht[8] = "Utrecht";
    char maastricht[11] = "Maastricht";
    char nijmegen[9] = "Nijmegen";
    char zwolle[7] = "Zwolle";
    char enschede[9] = "Enschede";
    char meppel[7] = "Meppel";
    char leeuwarden[11] = "Leeuwarden";
    char groningen[10] = "Groningen";
    if(strcmp(s, amsterdam) == 0) return 1;
    if(strcmp(s, haag) == 0) return 2;
    if(strcmp(s, eindhoven) == 0) return 3;
    if(strcmp(s, utrecht) == 0) return 4;
    if(strcmp(s, maastricht) == 0) return 5;
    if(strcmp(s, nijmegen) == 0) return 6;
    if(strcmp(s, zwolle) == 0) return 7;
    if(strcmp(s, enschede) == 0) return 8;
    if(strcmp(s, meppel) == 0) return 9;
    if(strcmp(s, leeuwarden) == 0) return 10;
    if(strcmp(s, groningen) == 0) return 11;
    return 0;
}

int main(int argc, char const *argv[]) {
    char *s = readInput();
    printf("%d\n", cityToId(s));
    return 0;
}
