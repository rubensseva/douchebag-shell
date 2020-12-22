#include <string.h>
#include <stdio.h>

#include "../utils/constants.h"

int parse_command(char *command, int *command_index) {
  *command_index = -1;
  for (int i = 0; i < 256; i++) {
    if (strcmp(command, get_commands(i)) == 0) {
      *command_index = i;
      break;
    }
  }
  
  return 0;
}
