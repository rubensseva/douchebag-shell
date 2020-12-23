#ifndef COMMANDS_MAP
#define COMMANDS_MAP

typedef struct Command {
   char  command[256];
   int (*action)(char** args, int length);
} command;


int notImplemented(char** args, int length);
int cd(char** args, int length);
int clr(char** args, int length);
int dir(char** args, int length);
int environ_func(char** args, int length);
int echo(char** args, int length);
int help(char** args, int length);
int pause_func(char** args, int length);
int quit(char** args, int length);

extern const command commands_list[];

#endif
