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
#include "./utils/env.h"
#include "./command/command-map.h"



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

  char *parent_bin_env_var = create_parent_bin_env_var();
  if (putenv(parent_bin_env_var) != 0) {
    perror("putenv");
  }

  printf("Oh... It's you again... What do you want?\n");

  // Prepare to read if input is a file
  FILE *stream;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  // If shell was invoked with arg, it is an input file
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
        char *child_bin_env_var = create_child_bin_env_var();
        if (putenv(child_bin_env_var) != 0) {
          perror("putenv");
        }
        execvp(strs[0], strs); // Replace the entire child process with the command to execute
        perror("Error when exetucing command");
        _exit(EXIT_FAILURE);
      } else {
        // We are in the parent process
        wait(NULL); // Wait for child process to finish
      }
    }
  }
  exit(EXIT_SUCCESS);
}
