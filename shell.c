#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <string.h>

#include "./utils/constants.h"
#include "./input/sanitation.h"
#include "./input/processing.h"
#include "./input/parsing.h"


int main() {
  char read[256];
  scanf("%[^\t\n]", read);

  int size = strlen(read);

  char **strs = (char **) malloc(256);
  for (int i = 0; i < 256; i++) {
    strs[i] = (char *) malloc(256);
  }

  int num_words;
  int split_err = split_string(read, size, strs, &num_words);
  if (split_err != 0) {
    printf("Error when splitting strings");
    return 1;
  }

  char *command = strs[0];
  int command_index;
  int err = parse_command(command, &command_index);
  if (err != 0) {
    printf("Command not recognized\n");
    return 1;
  }
  printf("Running command: %s\n", get_commands(command_index));

  return 1;
}
