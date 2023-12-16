#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_command(char *command)
{
	pid_t child_pid;
	int status;
	
	child_pid = fork();
	
	if (child_pid == -1)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	
	if (child_pid == 0)
	{
		/* Child process */
		char *args[] = {"/bin/sh", "-c", command, NULL};
		if (execvp(args[0], args) == -1)
		{
			perror("execve error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		waitpid(child_pid, &status, 0);
	}
}

int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
		printf("($) ");
		read = getline(&line, &len, stdin);
		if (read == -1)
		{
			perror("getline error");
			exit(EXIT_FAILURE);
		}

		// Remove newline character
		line[strcspn(line, "\n")] = '\0';

		if (strcmp(line, "exit") == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}

		execute_command(line);
	}

	free(line);
	return 0;
}
