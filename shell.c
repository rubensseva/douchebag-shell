#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#include "./utils/constants.h"
#include "./input/sanitation.h"
#include "./input/processing.h"
/* #include "./input/parsing.h" */ // not used yet


int main() {
  printf("Oh... It's you again... What do you want?\n");

  while(1) {
    char read[256];
    printf(">>> ");
    scanf(" %[^\t\n]", read);
    int size = strlen(read);

    char **strs = (char **) malloc(256);
    for (int i = 0; i < 256; i++) {
      strs[i] = (char *) malloc(256);
    }

    int num_words;
    int split_err = split_string(read, size, strs, &num_words);
    if (split_err != 0) {
      printf("Error when splitting strings\n");
      return 1;
    }
    strs[num_words] = NULL;

    char *command = strs[0];
    int command_index;

    // We need to detect for cd command so we change the working
    // dir of the actuall shell process, and not the child process
    if (strcmp(strs[0], "cd") == 0) {
      printf("Detected cd command, manually executing chdir...\n");
      int err = chdir(strs[1]);
      if (err != 0) {
        printf("Error when changing directory! Did you specify a correct path?: %s\n", strs[1]);
      } else {
        printf("Dir changed successfully\n");
      }
    } else {
      int pid = fork();
      if (pid == 0) {
        // We are in the child process
        execvp(strs[0], strs); // Replace the entire child process with the command to execute
      } else {
        // We are in the parent process
        wait(NULL); // Wait for child process to finish
      }
    }
  }
  return 0;
}
