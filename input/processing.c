#include <stdio.h>
#include <stdlib.h>


/*
 * Split string by whitespace
 */
int split_string(char *str, int size, char **strs, int *total_num_words) {
  char *curr_word = (char *) malloc(256);
  int curr_word_index = 0;
  int num_words = 0;
  for (int i = 0; i < size; i++) {
    if (str[i] == ' ') {
      if(i == 0) {
        printf("Sorry, can't start a program with whitespace, crashing now\n");
        return 1;
      }
      curr_word[curr_word_index + 1] = '\0';
      strs[num_words] = curr_word;
      num_words++;
      curr_word = (char *) malloc(256);
      curr_word_index = 0;
    } else {
      curr_word[curr_word_index] = str[i];
      curr_word_index++;
    }
  }
  curr_word[curr_word_index + 1] = '\0';
  strs[num_words] = curr_word;
  num_words++;
  *total_num_words = num_words;
  return 0;
}
