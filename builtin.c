#include "simple_shell.h"


/**
 * validate_command_syntax - checks if the command syntax is valid or not.
 * @buffer: input to check.
 * Return: return 0 if the syntax is correct, otherwise return -1.
 */
int validate_command_syntax(char *buffer)
{
    /*Flag to track command separator presence*/
	int flag = 0;
    /*just a Loop counter*/
    int i = 0;
    /*Variable to store syntax error status*/
    int syntax_error = 0; 

	while (buffer[i])
	{
		if (buffer[i] == ';' && flag == 1)
		{
            /* Syntax error: consecutive command separators */ 
			syntax_error = -1;
			break;
		}
		else if (buffer[i] == ';' && flag == 0)
		{
            /*Command separator found*/
			flag = 1;
		}
		else if (buffer[i] != ';' && buffer[i] != ' ' && flag == 1)
		{
            /*Reset flag if non-space character found after command separator*/
			flag = 0;
		}
		i++;
	}

	return syntax_error;
}

/**
 * display_command_help - displays help information for specific input commands.
 * @input: input for which help is displayed.
 */
void display_command_help(char **input)
{
	char *str;

	if (input[1] != NULL)
	{
		if (!str_comp(input[1], "help") == 0)
		{
			str = "help: help [pattern ...]\n";
			write(STDOUT_FILENO, str, str_len(str));
			str = "\tDisplay information about builtin commands.\n\n";
			write(STDOUT_FILENO, str, str_len(str));
			str = "\tDisplays brief summaries of built-in commands. If PATTERN is\n";
			write(STDOUT_FILENO, str, str_len(str));
			str = "\tspecified, gives detailed help on all commands matching PATTERN,\n";
			write(STDOUT_FILENO, str, str_len(str));
			str = "\totherwise the list of help topics is printed.\n\n";
			write(STDOUT_FILENO, str, str_len(str));
			str = "\tArguments:\n";
			write(STDOUT_FILENO, str, str_len(str));
			str = "\t  PATTERN   Pattern specifying a help topic\n";
			write(STDOUT_FILENO, str, str_len(str));
		}
		else if (!str_comp(input[1], "exit"))
		{
			str = "exit: exit\n";
			write(STDOUT_FILENO, str, str_len(str));
			str = "\tExit the shell.\n";
			write(STDOUT_FILENO, str, str_len(str));
		}
	}
	else
	{
		str = "These shell commands are defined internally.\n";
		write(STDOUT_FILENO, str, str_len(str));
		str = "Type `help name' to find out more about the function `name'.\n\n";
		write(STDOUT_FILENO, str, str_len(str));
		str = " help [pattern ...]\n";
		write(STDOUT_FILENO, str, str_len(str));
		str = " exit\n";
		write(STDOUT_FILENO, str, str_len(str));
	}
}
