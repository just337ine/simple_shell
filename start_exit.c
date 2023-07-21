#include "shs.h"

/**
 * exec_line - finds built-ins and commands
 *
 * @shdata: data relevant (args)
 * Return: 1 on success.
 */
int exec_line(shell_data *shdata)
{
	int (*builtin)(shell_data *shdata);

	if (shdata->args[0] == NULL)
		return (1);

	builtin = get_builtin(shdata->args[0]);

	if (builtin != NULL)
		return (builtin(shdata));

	return (cmd_execve(shdata));
}

/**
 * exit_shell - exits the shell
 *
 * @shdata: data relevant (status and args)
 * Return: 0 on success.
 */
int exit_shell(shell_data *shdata)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (shdata->args[1] != NULL)
	{
		ustatus = _atoi(shdata->args[1]);
		is_digit = _isdigit(shdata->args[1]);
		str_len = _strlen(shdata->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			error_code(shdata, 2);
			shdata->status = 2;
			return (1);
		}
		shdata->status = (ustatus % 256);
	}
	return (0);
}
