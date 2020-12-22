#include <stdlib.h>

const char* get_commands(size_t id) {
  static const char* const commands[] = {
    "cd", "clr", "dir", "environ", "echo", "help", "pause", "quit"
  };
  return (id < (sizeof(commands) / sizeof(commands[0])) ? commands[id] : "");
}
