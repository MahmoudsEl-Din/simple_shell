#include "simple_shell.h"

/**
 * handle_interrupt - Signal handler for the CTRL+C signal.
 * @signal: The signal number.
 */
void handle_interrupt(__attribute__((unused)) int input_signal)
{
	signal(SIGINT, handle_interrupt);
	write(STDOUT_FILENO, "\n", 1);
	write(STDOUT_FILENO, "\033[0;36mhsh# \033[0m", 16);
}


/**
 * printError - print specific errors to the outputs.
 * @file_id: The id of the shell.
 * @input: input that make the error.
 * @errorNum: identifies the error type.
 */
void printError(char *file_id, char *input, int errorNum)
{
	char *str;

	if (errorNum == 127) /* Sorry, command not found */
	{
		write(STDOUT_FILENO, file_id, str_len(file_id));
		write(STDOUT_FILENO, ": 1: ", 5);
		write(STDOUT_FILENO, input, str_len(input));
		write(STDOUT_FILENO, ": not found!!\n", 12);
	}
	if (errorNum == 2) /* any syntax error*/
	{
		str = "sh: 1: there are some Syntax error: \"";
		write(STDOUT_FILENO, str, str_len(str));
        write(STDOUT_FILENO, input, str_len(input));
		write(STDOUT_FILENO, ";", 1);
		str = "\" unexpected...\n";
		write(STDOUT_FILENO, str, str_len(str));
	}
	if (errorNum == 3) /* Memory allocation error */
	{
		write(STDOUT_FILENO, file_id, str_len(file_id));
		write(STDOUT_FILENO, ": 1: ", 5);
		str = "Sorry, Internal error allocating memory\n";
		write(STDOUT_FILENO, str, str_len(str));
	}
    if (errorNum == 4) /* Invalid argument */
    {
	write(STDOUT_FILENO, file_id, strlen(file_id));
	write(STDOUT_FILENO, ": 1: ", 5);
	str = "Sorry, Invalid argument: ";
	write(STDOUT_FILENO, str, str_len(str));
	write(STDOUT_FILENO, input, str_len(input));
	write(STDOUT_FILENO, "\n", 1);
    }
    if (errorNum == 5) /* File not found */
    {
	write(STDOUT_FILENO, "Error: File not found: ", 23);
	write(STDOUT_FILENO, input, strlen(input));
	write(STDOUT_FILENO, "\n", 1);
    }
}

