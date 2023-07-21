#include "shs.h"

/**
 * _help_info_env - Provides help information for the builtin env command.
 * Return: No return value.
 */
void _help_info_env(void)
{
	char *help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Print the environment of the shell.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * _help_info_setenv - Provides help information
 * for the builtin setenv command.
 * Return: No return value.
 */
void _help_info_setenv(void)
{
	char *help = "setenv: setenv (const char *name, const char *value, ";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "int replace)\n\t";
	help = "Add a new definition to the environment.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * _help_info_unsetenv - Provides help information
 * for the builtin unsetenv command.
 * Return: No return value.
 */
void _help_info_unsetenv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Remove an entry completely from the environment.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * _help_info_exit - Provides help information for the builtin exit command.
 * Return: No return value.
 */
void _help_info_exit(void)
{
	char *help = "exit: exit [n]\n";

	help = "Exit shell.\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "Exits the shell with a status of N. If N is omitted, the exit ";
	help = "status is that of the last command executed.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}
/**
 * get_help - function that retrieves help messages according to the builtin
 * @shdata: data structure (args and input)
 * Return: 1
 */
int get_help(shell_data *shdata)
{
	if (shdata->args[1] == NULL)
		_help_info();
	else if (_strcmp(shdata->args[1], "setenv") == 0)
		_help_info_setenv();
	else if (_strcmp(shdata->args[1], "env") == 0)
		_help_info_env();
	else if (_strcmp(shdata->args[1], "unsetenv") == 0)
		_help_info_unsetenv();
	else if (_strcmp(shdata->args[1], "help") == 0)
		cmd_help();
	else if (_strcmp(shdata->args[1], "exit") == 0)
		_help_info_exit();
	else if (_strcmp(shdata->args[1], "cd") == 0)
		change_cd_help();
	else if (_strcmp(shdata->args[1], "alias") == 0)
		aux_help_alias();
	else
		write(STDERR_FILENO, shdata->args[0],
				_strlen(shdata->args[0]));

	shdata->status = 0;
	return (1);
}
