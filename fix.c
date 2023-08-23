#include "simple_shell.h"

void executeCommand(int exit_status)
{
    exit_status = system("some_command_that_fails");
    if (exit_status == -1)
    {
        perror("Command execution failed");
        return;
    }
        else if (WIFEXITED(exit_status))
        {
            int exit_code = WEXITSTATUS(exit_status);
            printf("Command exited with status code: %d\n", exit_code);
        }
        else if (WIFSIGNALED(exit_status))
        {
            int signal_number = WTERMSIG(exit_status);
            printf("Command terminated by signal: %d\n", signal_number);
        }
}
