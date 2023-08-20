#include "simple_shell.h"

/**
 * check_builtin - checks
 * @command: command to check
 * Return: let's returns 0 if successful otherwsise returns -1.
 */
int check_builtin(char *command)
{
	if (!str_comp(command, "exit"))
		return (0);
	if (!str_comp(command, "env"))
		return (0);
	if (!str_comp(command, "help"))
		return (0);
	return (-1);
}


/**
 * check_builtin_commands - checks if the input corresponds to a built-in command.
 * @input: command input.
 * @env: the environment variables.
 * Return: 0 if no built-in command is executed, 1 if executed, -1 on error.
 */
int check_builtin_commands(char **input, char **env)
{
	int i = 0;
	char *str;

	if (!str_comp(input[0], "exit"))
	{
		freeArgv(input);
		return (2);
	}
	if (!str_comp(input[0], "help"))
	{
		display_command_help(input);
		return (1);
	}
	if (!str_comp(input[0], "env"))
	{
		i = 0;

		while (env[i])
		{
			str = env[i];
			write(STDOUT_FILENO, str, str_len(str));
			write(STDOUT_FILENO, "\n", 1);
			i++;
		}
		return (1);
	}

	return (0);
}
