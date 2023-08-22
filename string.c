#include "simple_shell.h"

/**
 * str_cpy - copies the string pointed to by src, including the null byte.
 * @dest: destination buffer.
 * @src: the string source.
 * Return: pointer to dest.
 */
char *str_cpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';

	return (dest);
}

/**
 * str_count - counts the number of times the char c is used in the buffer.
 * @buffer: buffer to check.
 * @c: char
 * Return: counter +1
 */
int str_count(char *buffer, char c)
{
	int i = 0;
	int counter = 0;

	while (buffer[i])
	{
		if (buffer[i] == c)
			counter++;
		i++;
	}

	return (counter + 1);
}

/**
 * is_not_empty - checks if input buffer contains only spaces.
 * @input_buffer: the command line that need to be executed.
 * Return: 0 if input_buffer contains only spaces, otherwise -1.
 */
int is_not_empty(char *input_buffer)
{
	int i = 0;
	int boolean = 0;

	while (input_buffer[i])
	{
		if (input_buffer[i] != ' ')
			break;
		i++;
	}
	if (input_buffer[i] && input_buffer[i] != '\n')
		boolean = -1;

	return (boolean);
}

/**
 * *str_cat - link two strings.
 * @dest: destination buffer.
 * @src: the source of string.
 * Return: pointer to the resulting string destination.
 */
char *str_cat(char *dest, char *src)
{
	int i, j;
	char *ptr = dest;

	if (src == NULL)
		return (ptr);
	for (i = 0; dest[i] != '\0'; i++)
	;
	for (j = 0; src[j] != '\0'; i++, j++)
		dest[i] = src[j];
	dest[i] = '\0';

	return (ptr);
}
