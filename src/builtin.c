#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtin.h"

/*
 * shared instance
 */
struct lsh_builtins lsh_builtins;

//static method declarations (private)
static void lsh_reg_builtins();
static void lsh_builtins_ensure_size(int size);
static void lsh_reg_builtin(char *name, int (*func) (char **));

static void lsh_reg_builtins()
{
   lsh_reg_builtin("cd", &lsh_cd);
   lsh_reg_builtin("help", &lsh_help);
   lsh_reg_builtin("exit", &lsh_exit);
}

/**
   @brief Bultin command: change directory.
   @param args List of args.  args[0] is "cd".  args[1] is the directory.
   @return Always returns 1, to continue executing.
 */
int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("lsh");
    }
  }
  return 1;
}

/**
   @brief Builtin command: print help.
   @param args List of args.  Not examined.
   @return Always returns 1, to continue executing.
 */
int lsh_help(char **args)
{
  int i;

  printf("Stephen Brennan's LSH\n");
  printf("Type program names and arguments, and hit enter.\n");
  printf("The following are built in:\n");

  for (i=0; i<lsh_builtins.count; i++) {
    printf("  %s\n", lsh_builtins.names[i]);
  }

  printf("Use the man command for information on other programs.\n");
  return 1;
}

/**
   @brief Builtin command: exit.
   @param args List of args.  Not examined.
   @return Always returns 0, to terminate execution.
 */
int lsh_exit(char **args)
{
  return 0;
}

void lsh_init_builtins()
{
   lsh_builtins.count = 0;
   lsh_builtins.alloc = 10;
   lsh_builtins.names = malloc(10*sizeof(void*));
   lsh_builtins.funcs = malloc(10*sizeof(void*));

   lsh_reg_builtins();
}

static void lsh_builtins_ensure_size(int size)
{
   while (lsh_builtins.alloc < size)
   {
      lsh_builtins.alloc *= 2;
      lsh_builtins.names = realloc(lsh_builtins.names, lsh_builtins.alloc*sizeof(void*));
      lsh_builtins.funcs = realloc(lsh_builtins.funcs, lsh_builtins.alloc*sizeof(void*));
   }
}

static void lsh_reg_builtin(char *name, int (*func) (char **))
{
   lsh_builtins_ensure_size(lsh_builtins.count+1);
   lsh_builtins.names[lsh_builtins.count] = name;
   lsh_builtins.funcs[lsh_builtins.count] = func;
   lsh_builtins.count++;
}
