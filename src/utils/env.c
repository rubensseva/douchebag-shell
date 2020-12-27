#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>




char *create_parent_bin_env_var() {
  char *shell_bin_path = (char *) malloc(256 * sizeof(char));
  int r = readlink("/proc/self/exe", shell_bin_path, 256);
  if (r == -1) {
    perror("readlink");
  }
  shell_bin_path[r] = '\0';
  char *shell_env = (char *) malloc(256 * sizeof(char));
  strcpy(shell_env, "shell=");
  strcat(shell_env, shell_bin_path);
  return shell_env;
}

char *create_child_bin_env_var() {
  char *shell_bin_path = (char *) malloc(256 * sizeof(char));
  int r = readlink("/proc/self/exe", shell_bin_path, 256);
  if (r == -1) {
    perror("readlink");
  }
  shell_bin_path[r] = '\0';
  char *shell_env = (char *) malloc(256 * sizeof(char));
  strcpy(shell_env, "parent=");
  strcat(shell_env, shell_bin_path);
  return shell_env;
}
