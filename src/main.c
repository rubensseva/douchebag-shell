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
#include "./utils/env.h"



int main(int argc, char **argv) {
  printf("%d\n", argc);
  if (argc > 2) {
    printf("To many input arguments, exiting...\n");
    return 1;
  } else if (argc == 2) {
    printf("Got one input argument: %s\n", argv[0]);
  } else {
    printf("No input argument, scanning input...\n");
  }

  /* char shell_bin_path[256]; */
  /* int r = readlink("/proc/self/exe", shell_bin_path, 256); */
  /* shell_bin_path[r] = '\0'; */
  /* char shell_env[256] = "shell="; */
  /* strcat(shell_env, shell_bin_path); */
  /* putenv(shell_env); */
  set_bin_path_parent();

  printf("Oh... It's you again... What do you want?\n");

  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  if (argc == 2) {
    stream = fopen(argv[1], "r");
    if (stream == NULL) {
      perror("fopen");
      exit(EXIT_FAILURE);
    }
  }

  while(1) {
    char *read = (char *) malloc(256);
    int size;

    if (argc == 1) {
      printf(">>> ");
      scanf(" %[^\t\n]", read);
      size = strlen(read);
    } else if (argc == 2) {
      nread = getline(&line, &len, stream);
      if (nread == -1) {
        printf("Done reading from file");
        break;
      }
      line[nread - 1] = '\0';
      read = line;
      size = nread;
    }


    char **strs = (char **) malloc(256);
    for (int i = 0; i < 256; i++) {
      strs[i] = (char *) malloc(256);
    }

    int num_words;
    int split_err = split_string(read, size, strs, &num_words);
    if (split_err != 0) {
      printf("Error when splitting strings\n");
      exit(EXIT_FAILURE);
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
        /* char shell_env[256] = "parent="; */
        /* strcat(shell_env, shell_bin_path); */
        /* putenv(shell_env); */
        set_bin_path_child();
        execvp(strs[0], strs); // Replace the entire child process with the command to execute
        printf("Something went wrong when trying to execute command... Are you sure the command exists?\n"); // Should not get here
        _exit(EXIT_FAILURE);
      } else {
        // We are in the parent process
        wait(NULL); // Wait for child process to finish
      }
    }
  }
  exit(EXIT_SUCCESS);
}
