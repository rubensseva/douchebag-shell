

typedef struct Command {
   char  command[256];
   int (*action)(char** args, int length);
} command;
