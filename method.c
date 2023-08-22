#include "simple_shell.h"


/**
 * run - runs the interactive shell.
 * @path: Pointer to the list of directories in the PATH.
 * @env: the environment variables.
 * @file_id: The id of the shell.
 * @method: run in interactive or non-interactive method.
 * Return: Always returns 0.
 */
int run(list_t *path, char **env, char *file_id, int method)
{
	char *buffer = NULL;
	int status, line_status;
	size_t buffer_size = 0;

	while (1)
	{
		if (method == 1)
			write(STDOUT_FILENO, "\033[0;36mhsh# \033[0m", 16);
		signal(SIGINT, handle_interrupt);
		line_status = getline(&buffer, &buffer_size, stdin);
		if (line_status == -1)
		{
			if (line_status == EOF)
			{
				free(buffer);
				if (method == 1)
					write(STDOUT_FILENO, "\n", 1);
				return (status);
			}
			printError(file_id, buffer, 3);
		}

/*
* If the input buffer contains only spaces
* or the '\n' character, the prompt will be shown again
*/
		status = execute_command_line(buffer, path, env, file_id);
		if (status == -1 || status == 127 || status == 2)
		{
			if (status == -1)
				perror("SORRY, COMMAND NOT FOUND");
			free(buffer);
			break;
		}
	}
	return (status);
}


/**
 * execute_command_line - command line.
 * @buffer: command line to execute.
 * @path: pointer to the list of directories in the PATH.
 * @env: the environment variable.
 * @file_id: The id of the shell.
 * Return: Always returns 0.
 */
int execute_command_line(char *buffer, list_t *path, char **env, char *file_id)
{
	char *clean_command_line, *input_buffer, *new_buffer;
	int port, syntax_check, execution_result = 0;

	clean_command_line = removeComments(buffer);
	input_buffer = str_tr(clean_command_line, '\t', ' ');
	if (is_not_empty(input_buffer))
	{
		syntax_check = str_count(input_buffer, ';');
		if (syntax_check > 1)
		{
			port = validate_command_syntax(input_buffer);
			if (port == -1)
			{
				printError(file_id, input_buffer, 2);
				free(input_buffer);
				free(clean_command_line);
				return (-1);
			}
			new_buffer = str_tr(input_buffer, ';', '\n');
		}
		else
			new_buffer = str_dup(input_buffer);

		execution_result = run_command(new_buffer, path, env, syntax_check, file_id);
		free(new_buffer);
	}
	free(input_buffer);
	free(clean_command_line);
	return (execution_result);
}

/**
 * run_command - run command.
 * @new_buffer: new command line to execute.
 * @path: pointer to the list of directories in the PATH.
 * @env: the environment variable.
 * @syntax_check: number of separate commands.
 * @file_id: The id of the shell.
 * Return: let's returns 0 if successful , 1 if sorry, command not found, or 2
 */
int run_command(char *new_buffer, list_t *path, char **env,
						int syntax_check, char *file_id)
{
	char *temp_buffer, *current_buffer;
	char **input;
	int i, port, current, execution_result = 0;

	current = 0;
	while (current < syntax_check)
	{
		temp_buffer = str_dup(new_buffer);
		current_buffer = strtok(temp_buffer, "\n");
		for (i = 0; i < current; i++)
			current_buffer = strtok(NULL, "\n");
		input = createArgumentVector(current_buffer, &path);
		port = check_builtin_commands(input, env);
		if (port == 2)
		{
			free(temp_buffer);
			return (2);
		}
		if (port == 0)
		{
			execution_result = run_fork(input, file_id);
		}
		freeArgv(input);
		free(temp_buffer);
		current++;
	}
	return (execution_result);
}

