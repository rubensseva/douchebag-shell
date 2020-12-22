#include <stdio.h>
#include <unistd.h>

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

