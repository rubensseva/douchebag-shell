#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

#include "./commands-map.h"

const command commands_list[] = { 
  { .command = "cd",      .action = cd },
  { .command = "clr",     .action = clr },
  { .command = "dir",     .action = dir },
  { .command = "environ", .action = environ_func },
  { .command = "echo",    .action = echo },
  { .command = "help",    .action = help },
  { .command = "pause",   .action = pause_func },
  { .command = "quit",    .action = quit },
};

extern char **environ;

int notImplemented(char** args, int length) {
  printf("You entered a builtin command, but it's not implemented yet...\n");
}

int cd(char** args, int length) {
  printf("Detected cd command, manually executing chdir...\n");
  int err = chdir(args[1]);
  if (err != 0) {
    printf("Error when changing directory! Did you specify a correct path?: %s\n", args[1]);
    return 1;
  } else {
    printf("Dir changed successfully\n");
    return 0;
  }
}

int clr(char** args, int length) {
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
  return 0;
}

int dir(char** args, int length) {
  printf("Detected dir command, manually listing contents of directory...\n");
  printf("Directory to list: %s\n", args[1]);
  DIR *d;
  struct dirent *dir;
  if (length <= 1) {
    d = opendir(".");
  } else {
    d = opendir(args[1]);
  }
  if (d)
  {
      while ((dir = readdir(d)) != NULL)
      {
          printf("%s ", dir->d_name);
      }
      printf("\n");
      closedir(d);
  }
  return(0);
}

int environ_func(char** args, int length) {
  printf("Detected environ command, manually listing env vars...\n");
  char *s = *environ;
  for (int i = 1; s; i++) {
    printf("%s\n", s);
    s = *(environ+i);
  }
  return 0;
}

int echo(char** args, int length) {
  printf("Detected echo command, manually printing comment\n");
  if (length <= 0) {
    printf("Didnt find any comment to print...");
    return 1;
  }
  for (int i = 1; i < length; i++) {
    printf("%s ", args[i]);
  }
  printf("\n");
  return 0;
}

int help(char** args, int length) {
  printf("help command is not implemented yet\n");
  return 0;
}

int pause_func(char** args, int length) {
  printf("pause command is not implemented yet\n");
  return 0;
}

int quit(char** args, int length) {
  printf("Detected quit command, manually exiting...\n");
  printf("Exiting...\n");
  exit(0);
  return 0;
}
