#include "shell.h"
/**
 * main - simple shell main function
 * @ac: count of arguments
 * @av: arguments
 * Return: 0 always (success).
 */
int main(int ac, char **argv)
{
	char *line = NULL;
	char **command = NULL;
       int status;
(void) ac;


