// implements a dictionary

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dictionary.h"

dict *newEmptyDict() {
  dict *d = malloc(sizeof(dict));
  if (d == NULL) {
    return NULL;
  }
  d->numWords = 0;
  d->maxWords = 1;
  d->words = malloc(sizeof(char*) * d->maxWords);
  return d;
}

// add word to the dictionary if it is is not already known
void addWord(char word[LENGTH + 1], dict *d) {
  if (!check(word, d)) {
    // if we need more space before adding the word, double the size
    if (d->numWords == d->maxWords) {
      d->words = realloc(d->words,(sizeof(char*)) * (d->maxWords * 2));
      if (d->words == NULL) {
        printf("Out of memory.\n");
        exit(-1);
      }
      d->maxWords = d->maxWords * 2;
    }
    // now we actually add the word
    d->words[d->numWords] = malloc(sizeof(char) * (LENGTH + 1));
    strcpy(d->words[d->numWords],word);
    d->numWords++;
  }
}

// check whether word is in dictionary
bool check(const char *word, dict *d) {
  for (int i = 0; i < d->numWords; i++) {
    if (strcmp(d->words[i],word) == 0) {
      return true;
    }
  }
  return false;
}

void freeDict(dict *d) {
  for (int i = 0; i < d->numWords; i++) {
    free(d->words[i]);
  }
  free(d->words);
  free(d);
}


trie newTrie(){
    trie new = malloc(sizeof(struct trie));
    assert (new != NULL);
    new->is_word = 0;
    for(int i=0; i<N; i++){
        new->children[i] = NULL;
    }
    return new;
}

void addWordToTrie(trie t, char word[LENGTH + 1]){
    int i = 0;
    while(word[i] != 0){
        if(t->children[word[i] - 'a'] == NULL){
            t->children[word[i] - 'a'] = newTrie();
        }
        t = t->children[word[i] - 'a'];
        i++;
    }
    t->is_word=1;
}

void freeTrie(trie t){
    for(int i = 0; i<N; i++){
        if(t->children[i] != NULL) freeTrie(t->children[i]);
    }
    free(t);
}

void printTrie(trie t){
    if(t->is_word==1)    printf("\n");
    for(int i = 0; i<N; i++){
        if(t->children[i] != NULL){
            printf("%c ", 'a' + i);
            printTrie(t->children[i]);
        }
        // if(t->is_word == 1 ) printf("\tend of word\n");
    }
}

bool checkTrie(char word[LENGTH+1], trie t){
    int i = 0;
    while(word[i] != '\0'){
        if(t->children[word[i] - 'a'] == NULL){
            return false;
        }
        t = t->children[word[i] - 'a'];
        i++;
    }
    if(t->is_word==1) return true;
    else return false;
}
