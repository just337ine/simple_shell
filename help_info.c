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
 * _help_info_setenv - Provides help information for the builtin setenv command.
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
 * _help_info_unsetenv - Provides help information for the builtin unsetenv command.
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
