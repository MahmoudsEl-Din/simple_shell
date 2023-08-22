#include "simple_shell.h"


/**
 * main - execute the shell (interactive or non-interactive methods).
 * @ac: argumen count.
 * @av: argument vector.
 * @env: the environment variables.
 * Return: always return 0.
 */
int main(__attribute__((unused)) int ac, char **av, char **env)
{
	list_t *path;
	char *file_id = av[0];
	int port = 0;
	int method = 0;

	signal(SIGINT, SIG_IGN);
	path = createPathList(env);
	if (isatty(0))
		method = 1;
	port = run(path, env, file_id, method);
	freeDirList(path);
	return (port);
}

/**
 * run_fork - Run acommand using fork.
 * @input: argv to execute.
 * @file_id: The id of the shell.
 * Return: let's returns 0 if successful otherwsise returns 127.
 */
int run_fork(char **input, char *file_id)
{
	int status, execution_result = 0;
	struct stat stat_status;
	pid_t pid = getpid();

	pid = fork();
	/* child executes, father waits */
	if (pid == 0)
	{
		if (execve(input[0], input, NULL) == -1)
		{
			printError(file_id, input[0], 127);
			execution_result = 127;
		}
	}
	else
	{
		wait(&status);
		if (stat(input[0], &stat_status) == -1)
			execution_result = 127;
	}

	return (execution_result);
}

