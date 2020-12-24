#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>




void set_bin_path_parent() {
  printf("Setting parent\n");
  char shell_bin_path[256];
  int r = readlink("/proc/self/exe", shell_bin_path, 256);
  if (r == -1) {
    printf("readlink error\n");
    perror("readlink");
  }
  shell_bin_path[r] = '\0';
  char shell_env[256] = "shell=";
  strcat(shell_env, shell_bin_path);
  int res = putenv(shell_env);
  if (res != 0) {
    printf("putenv error\n");
    perror("putenv");
  }
  printf("%s\n", shell_env);
}

void set_bin_path_child() {
  char shell_bin_path[256];
  int r = readlink("/proc/self/exe", shell_bin_path, 256);
  shell_bin_path[r] = '\0';
  char shell_env[256] = "parent=";
  strcat(shell_env, shell_bin_path);
  putenv(shell_env);
}
