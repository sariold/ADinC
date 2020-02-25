
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "dictionary.h"

// remove non-alphabetic characters and convert to lower case
void trimWord(char *word) {
  int k = 0;
  for (int i = 0; i < (int) strlen(word); i++) {
    if (isalpha(word[i])) {
      word[k] = tolower(word[i]);
      k++;
    }
  }
  word[k] = '\0';
}

int main(int argc, char *argv[]) {

  char word[LENGTH + 1] = "";

  // step 1: read in the dictionary
  trie new = newTrie();
  while (scanf("%45s",word) && word[0] != '!') {
    trimWord(word);
    addWordToTrie(new, word);
  }

  // step 2: read in text
  int counter = 0; // number of unknown words

  int index = 0;
  int c = EOF;
  getchar();
  while ((c = getchar()) && c != EOF) {
    if(isalpha(c)){
        word[index] = tolower(c);
        index++;
    }
    else {
        word[index] = '\0';
        if(index > 0 && !checkTrie(word, new)){
            counter++;
            printf("%s\n", word);
        }
        index=0;
    }
  }

  // step 3: print number of unknown words
  printf("%d\n", counter);
  freeTrie(new);
  return 0;
}
