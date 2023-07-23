#include "shs.h"

/**
 * aux_help_alias - Provides help information for the builtin alias command.
 * Return: No return value.
 */
void aux_help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDefine or display aliases.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * change_cd_help - Provides help information for the builtin cd command.
 * Return: No return value.
 */
void change_cd_help(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tChange the shell working directory.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

/**
 * rev_string - Reverses a string.
 * @s: Input string.
 * Return: No return value.
 */
void rev_string(char *s)
{
	int length = 0;
	char *start = s;
	char *end = s;
	char temp;

	if (s == NULL)
		return;

	/* Find the end of the string */
	while (*end != '\0')
	{
		length++;
		end++;
	}

	end--; /* Set 'end' to the last character before the null terminator */

	/* Swap characters from both ends */
	while (start < end)
	{
		temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;
	}
}
