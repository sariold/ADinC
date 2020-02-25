// declares a dictionary

#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <stdbool.h>

// maximum length for a word
#define LENGTH 45
#define N 26

// a dictionary is an array
typedef struct dict {
  int numWords;
  int maxWords;
  char **words;
} dict;

typedef struct trie {
    bool is_word;
    struct trie *children[N];
} *trie;

dict *newEmptyDict();
void addWord(char word[LENGTH + 1], dict *d);
bool check(const char *word, dict *d);
void freeDict(dict *n);

void printTrie(trie t);
trie newTrie();
void addWordToTrie(trie t, char word[LENGTH + 1]);
void freeTrie(trie t);
bool checkTrie(char word[LENGTH+1], trie t);

#endif // DICTIONARY_H
