#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>

/**
 * struct list - representing a directory path list.
 * @dir: is directorry path.
 * @next: is just apointer to the next directory node.
 */
typedef struct list
{
	char *dir;
	struct list *next;
} list_t;

/*method.c*/
int run(list_t *path, char **env, char *file_id, int method);
int execute_command_line(char *buffer, list_t *path,
							char **env, char *file_id);
int run_command(char *new_buffer, list_t *path,
						char **env, int syntax_check, char *file_id);

/*MAIN.C*/
int run_fork(char **input, char *file_id);

/*builtin.c*/
int validate_command_syntax(char *buffer);
void display_command_help(char **input);


/*check_builtin.c*/
int check_builtin(char *command);
int check_builtin_commands(char **input, char **env);

/*error.c*/
void handle_interrupt(__attribute__((unused)) int signal);
void printError(char *file_id, char *input, int errorNum);

/*env.c*/
list_t *createPathList(char **env);
list_t *addNodeToList(list_t **head, char *dir);
list_t *createList(char **environ);
void freeDirList(list_t *head);

/*getline.c*/
char **createArgumentVector(char *input_buffer, list_t **path);
char *getPath(char *buffer, list_t **path);
char *port_getPath(list_t *pathList, char *slashCommand,
						char *slashInput, char *input);

/*memory.c*/
char *removeLeadingSpaces(char *buffer);
void freeArgv(char **argv);
char *removeComments(char *buffer);


/*string.c*/
char *str_cpy(char *dest, char *src);
int str_count(char *buffer, char c);
int is_not_empty(char *input_buffer);
char *str_cat(char *dest, char *src);

/*more_string.c*/
char *str_con(char *s1, char *s2);
char *str_tr(char *buffer, char old_char, char new_char);
int str_comp(char *s1, char *s2);
int str_len(char *s);
char *str_dup(char *str);

/*fix.c*/
void executeCommand(int exit_status);

#endif /* SIMPLE_SHELL_H */
