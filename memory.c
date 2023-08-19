#include "simple_shell.h"


/**
 * removeLeadingSpaces - remove spaces in the first position of the buffer.
 * @buffer: buffer to be cleaned.
 * Return: a new buffer equal without spaces in the first position(s).
 */
char *removeLeadingSpaces(char *buffer)
{
	int len, firstCharPosition, i = 0;
	char *new_buffer, *cleanedBuffer;

	new_buffer = str_dup(buffer);
	if (new_buffer[0] != ' ')
		return new_buffer;

	while (new_buffer[i] == ' ')
		i++;
	firstCharPosition = i;

	while (new_buffer[i])
		i++;
	len = i - firstCharPosition;

	cleanedBuffer = malloc(sizeof(char) * (len + 1));
	i = firstCharPosition;

	while (new_buffer[i])
	{
		cleanedBuffer[i - firstCharPosition] = new_buffer[i];
		i++;
	}

	cleanedBuffer[i - firstCharPosition] = '\0';

	free(new_buffer);
	return cleanedBuffer;
}


/**
 * frees memory allocated in the argument vector.
 * @argv: argument vector to be freed.
 */
void freeArgv(char **argv)
{
	int i = 0;

	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

/**
 * removeComments - removes the comments from the input buffer.
 * @buffer: buffer to be cleaned.
 * Return: a pointer to the new buffer without any comments.
 */
char *removeComments(char *buffer)
{
	char *cleanedBuffer;
	int i = 0;

	cleanedBuffer = malloc(sizeof(char) * (str_len(buffer) + 1));
	if (!cleanedBuffer)
	{
		perror("MALLOC");
		return (NULL);
	}

	while (buffer[i])
	{
		if (buffer[i] == '#')
			break;
		cleanedBuffer[i] = buffer[i];
		i++;
	}
	cleanedBuffer[i] = '\0';

	return cleanedBuffer;
}

