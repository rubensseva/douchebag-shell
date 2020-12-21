#include <stdlib.h>

const char* get_commands(size_t id) {
  static const char* const commands[] = {
    "cd", "pwd"
  };
  return (id < (sizeof(commands) / sizeof(commands[0])) ? commands[id] : "");
}
