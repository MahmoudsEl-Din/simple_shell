#include "simple_shell.h"


/**
 * createArgumentVector - converts input into an argument vector.
 * @input_buffer: the input to be processed.
 * @path: pointer to path list.
 * Return: pointer to the new argument vector.
 */
char **createArgumentVector(char *input_buffer, list_t **path)
{
	int i = 0,  ac = 0, argc = 1;
	char *currentToken, *tokenToPut, *newInput;
	char **argv;

	newInput = getPath(input_buffer, path);
	while (newInput[i])
	{
		if (newInput[i] == ' ' &&	/* Increment the counter */
			(newInput[i + 1] &&
				(newInput[i + 1] != ' ' &&
					newInput[i + 1] != '\n')))
			argc += 1;
		i++;
	}

	argv = malloc(sizeof(char *) * (argc + 1));
	if (argv == NULL)
	{
		write(STDOUT_FILENO, "MALLOC ERROR\n", 14);
		return (NULL);
	}

	currentToken = strtok(newInput, "\n");
	currentToken = strtok(currentToken, " ");
	while (ac < (argc + 1))
	{
		tokenToPut = str_dup(currentToken);	/* Duplicate the argument */
		argv[ac] = tokenToPut;
		currentToken = strtok(NULL, " ");
		ac++;

	}
	free(newInput);
	return (argv);
}


/**
 * getPath - get the directory path where the command is executable.
 * @buffer: all the command have been passed.
 * @path: pointer to path  list.
 * Return: pointer.
 */
char *getPath(char *buffer, list_t **path)
{
	char *input, *port, *command = NULL;
	char *slashCommand, *slashInput, *input_buffer;
	struct stat status;
	list_t *pathList = *path;

    /* Clean input in case the first character(s) are spaces */
	input_buffer = removeLeadingSpaces(buffer);
	input = str_dup(input_buffer);
	free(input_buffer);

    /* Extract the first argument from input */
	port = str_dup(input);
	command = strtok(port, " ");
	if (command == NULL)
		command = port;

    /* Check if the first argument is executable */
	if (stat(command, &status) == 0)
	{
		free(port);
		return (input);
	}
    /* Check if the first argument is a built-in command */
	if (check_builtin(command) == 0)
	{
		free(port);
		return (input);
	}
	slashCommand = str_con("/", command);
	slashInput = str_con("/", input);

	free(port);
	return (port_getPath(pathList, slashCommand, slashInput, input));
}


/**
 * port_getPath - obtain the directory path where the command is executable.
 * @pathList: pointer to directory in path list.
 * @slashCommand: string.
 * @slashInput: string.
 * @input: input string.
 * Return: pointer.
 */
char *port_getPath(list_t *pathList, char *slashCommand,
							char *slashInput, char *input)
{
	char *port;
	struct stat status;

	while (pathList)
	{
		/* Check if the command is executable in the current directory */
		port = str_con(pathList->dir, slashCommand);
		if (stat(port, &status) == 0)
			break;
		free(port);
		pathList = pathList->next;
	}

	/* check if command is executable */
	if (pathList && (stat(port, &status) == 0))
	{
		free(port);
		port = str_con(pathList->dir, slashInput);
		free(input);
		free(slashInput);
		free(slashCommand);
		return (port);
	}
	free(slashInput);
	free(slashCommand);
	return (input);
}

