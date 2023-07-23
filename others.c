#include "shs.h"

/**
 * free_line_list - Frees a line_list.
 *
 * @head: Address of the head of the linked list.
 *
 * Return: No return.
 */
void free_line_list(line_list **head)
{
	if (head)
	{
		line_list *curr = *head;

		while (curr)
		{
			line_list *temp = curr;

			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * msg_exit_shell - Generates a generic error message for the exit command.
 *
 * @shdata: Data structure containing relevant information.
 *
 * Return: Error message.
 */
char *msg_exit_shell(shell_data *shdata)
{
	int length;
	char *error;
	char *var_str;

	var_str = int_to_string(shdata->counter);
	length = _strlen(shdata->av[0]) + _strlen(var_str);
	length += _strlen(shdata->args[0]) + _strlen(shdata->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(var_str);
		return (NULL);
	}

	/* Concatenate program name, counter, command, and error message */
	_strcpy(error, shdata->av[0]);
	_strcat(error, ": ");
	_strcat(error, var_str);
	_strcat(error, ": ");
	_strcat(error, shdata->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, shdata->args[1]);
	_strcat(error, "\n\0");
	free(var_str);

	return (error);
}

/**
 * _help_info - Provides general help information for the help builtin.
 * Return: No return value.
 */
void _help_info(void)
{
	char *help = "^J-S^ > bash, version 1.0(1)-release\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "These commands are defined internally. Type 'help' to see the list.";
	help = " Type 'help name' to find out more about the function 'name'.\n\n ";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "alias: alias [name=['string']]\n cd: cd [-L|[-P [-e]] [-@]] [dir]";
	help = "exit: exit [n]\n";
	help = "env: env [option] [name=value] [command [args]]\n";
	help = "setenv: setenv [variable] [value]\n";
	help = "unsetenv: unsetenv [variable]\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * _getenv - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable
 *
 * Return: value of the environment variable if found.
 * Otherwise, returns NULL.
 */
char *_getenv(const char *name, char **_environ)
{
	char *ptr_env;
	int i, mov;

	ptr_env = NULL;
	mov = 0;

	for (i = 0; _environ[i]; i++)
	{
		mov = cmp_env_name(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * _env - prints the environment variables
 * @shdata: data relevant
 * Return: 1 on success
 */
int _env(shell_data *shdata)
{
	int i, j;

	for (i = 0; shdata->_environ[i]; i++)
	{
		for (j = 0; shdata->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, shdata->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}

	shdata->status = 0;
	return (1);
}

