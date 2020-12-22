typedef struct Command {
   char  command[256];
   int (*action)(char** args, int length);
} command;


int notImplemented(char** args, int length);
int cd(char** args, int length);

command commands_list[] = { 
  { .command = "cd",      .action = cd },
  { .command = "clr",     .action = notImplemented },
  { .command = "dir",     .action = notImplemented },
  { .command = "environ", .action = notImplemented },
  { .command = "echo",    .action = notImplemented },
  { .command = "help",    .action = notImplemented },
  { .command = "pause",   .action = notImplemented },
  { .command = "quit",    .action = notImplemented },
};
