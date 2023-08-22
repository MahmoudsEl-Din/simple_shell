#include "simple_shell.h"

/**
 * str_con - link two strings into a new memory address.
 * @s1: first string to be linked.
 * @s2: second string to be linked.
 * Return: memory address to the new string.
 */
char *str_con(char *s1, char *s2)
{
	char *result;

	result = malloc(str_len(s1) + str_len(s2) + 1);
	if (!result)
	{
		perror("MALLOC");
		return (NULL);
	}

	str_cpy(result, s1);
	str_cat(result, s2);
	return (result);
}

/**
 * str_tr - swap an old_char to new_char
 * @buffer: input buffer.
 * @old_char: char to be change with new one.
 * @new_char: the new char the repcaled.
 * Return: return
 */
char *str_tr(char *buffer, char old_char, char new_char)
{
	int i = 0;
	char *new_buffer;

	new_buffer = str_dup(buffer);
	while (buffer[i])
	{
		new_buffer[i] = buffer[i];
		i++;
	}

	i = 0;
	while (new_buffer[i])
	{
		if (new_buffer[i] == old_char)
			new_buffer[i] = new_char;
		i++;
	}

	return (new_buffer);
}

/**
 * str_comp - making a compares between a 2 strings.
 * @s1: input string 1.
 * @s2: input string 2.
 * Return: let's return 0 if s1 == s2, otherwise -1.
 */
int str_comp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (-1);
		i++;
	}
	if (s1[i] != s2[i])
		return (-1);

	return (0);
}

/**
 * str_len - return the length of an string.
 * @s: char.
 * Return: len
 */
int str_len(char *s)
{
	int i = 0;
	int e = 0;

	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		e++;
		i++;
	}
	return (e);
}


/**
 * str_dup - return a pointer to a new string as duplicate of string.
 * @str: the source of the sting to be duplicate.
 * Return: pointer to the duplicated string,
 * or NULL if str = NULL or if insufficient memory was available.
 */
char *str_dup(char *str)
{
	char *port;

	if (str == NULL)
		return (NULL);
	port = malloc(sizeof(char) * (str_len(str) + 1));
	if (port == NULL)
		return (NULL);
	return (str_cpy(port, str));
}
