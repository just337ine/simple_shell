#include "shs.h"

/**
 * get_len - Get the length of a number.
 *
 * @n: Integer number.
 *
 * Return: Length of the number.
 */
int get_len(int n)
{
	unsigned int n1;
	int length = 1;

	if (n < 0)
	{
		length++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}

	while (n1 > 9)
	{
		length++;
		n1 /= 10;
	}

	return length;
}

/**
 * int_to_string - Converts int to string.
 *
 * @n: Integer number.
 *
 * Return: String.
 */
char *int_to_string(int n)
{
	unsigned int n1;
	int length = get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (!buffer)
		return NULL;

	buffer[length] = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	length--;
	do {
		buffer[length] = (n1 % 10) + '0';
		n1 /= 10;
		length--;
	} while (n1 > 0);

	return buffer;
}

/**
 * _atoi - Converts a string to an integer.
 *
 * @s: Input string.
 *
 * Return: Integer.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, pn = 1, m = 1, i;

	while (s[count] != '\0')
	{
		if (size > 0 && (s[count] < '0' || s[count] > '9'))
			break;

		if (s[count] == '-')
			pn *= -1;

		if ((s[count] >= '0') && (s[count] <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	int oi = 0;
	for (i = count - size; i < count; i++)
	{
		oi = oi + ((s[i] - '0') * m);
		m /= 10;
	}
	return oi * pn;
}

/**
 * without_comment - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */
char *without_comment(char *in)
{
    int i, up_to;

    up_to = 0;
    for (i = 0; in[i]; i++)
    {
        if (in[i] == '#')
        {
            if (i == 0)
            {
                free(in);
                return (NULL);
            }

            if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
                up_to = i;
        }
    }

    if (up_to != 0)
    {
        in = _realloc(in, i, up_to + 1);
        in[up_to] = '\0';
    }

    return (in);
}

/**
 * cmd_help - Provides help information for the builtin help command.
 * Return: No return value.
 */
void cmd_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _strlen(help));
	help = "\tDisplay information about builtin commands.\n";
	write(STDOUT_FILENO, help, _strlen(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _strlen(help));
}

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