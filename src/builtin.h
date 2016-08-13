#ifndef LSH_BUILTIN_H
#define LSH_BUILTIN_H

struct lsh_builtins
{
   int count;
   int alloc;
   char **names;
   int (**funcs) (char **);
};

void lsh_init_builtins();

/*
 * Function Declarations for builtin shell commands:
 */
int lsh_cd(char **args);
int lsh_help(char **args);
int lsh_exit(char **args);

extern struct lsh_builtins lsh_builtins;

#endif //LSH_BUILTIN_H
