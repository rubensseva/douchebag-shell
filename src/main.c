#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#include "./input/sanitation.h"
#include "./input/processing.h"
#include "./input/parsing.h"
#include "./utils/constants.h"
#include "./utils/commands-map.h"



int main() {

  char linkname[256];
  int r = readlink("/proc/self/exe", linkname, 256);
  linkname[r] = '\0';
  char shell_env[256] = "shell=";
  strcat(shell_env, linkname);
  putenv(shell_env);

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
    parse_command(command, &command_index);

    if (command_index != -1) {
      int err = commands_list[command_index].action(strs, num_words);
      if (err != 0) {
        printf("Error when executing built-in command\n");
        continue;
      }
    } else {
      int pid = fork();
      if (pid == 0) {
        // We are in the child process
        execvp(strs[0], strs); // Replace the entire child process with the command to execute
        printf("Something went wrong when trying to execute command... Are you sure the command exists?\n"); // Should not get here
        return 0;
      } else {
        // We are in the parent process
        wait(NULL); // Wait for child process to finish
      }
    }
  }
  return 0;
}
