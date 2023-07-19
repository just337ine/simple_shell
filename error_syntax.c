#include "shs.h"

/**
 * count_char - counts the repetitions of a char
 *
 * @input: input string
 * @i: index
 * Return: repetitions
 */
int count_char(char *input, int i)
{
	if (*(input - 1) == *input)
		return (count_char(input - 1, i + 1));

	return (i);
}

/**
 * find_sy_error - finds syntax errors
 *
 * @input: input string
 * @i: index
 * @last: last char read
 * Return: index of error. 0 when there are no errors
 */
int find_sy_error(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (find_sy_error(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = count_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = count_char(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (find_sy_error(input + 1, i + 1, *input));
}

/**
 * first_char_input - finds index of the first char
 *
 * @input: input string
 * @i: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char_input(char *input, int *i)
{
	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * syntax_error_info - prints when a syntax error is found
 *
 * @shdata: data structure
 * @input: input string
 * @i: index of the error
 * @bool: to control msg error
 * Return: no return
 */
void syntax_error_info(shell_data *shdata, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = int_to_string(shdata->counter);
	length = _strlen(shdata->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (!error)
	{
		free(counter);
		return;
	}
	_strcpy(error, shdata->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_syntax_error - intermediate function to find and print a syntax error
 *
 * @shdata: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syntax_error(shell_data *shdata, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_char_input(input, &begin);
	if (f_char == -1)
	{
		syntax_error_info(shdata, input, begin, 0);
		return (1);
	}

	i = find_sy_error(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		syntax_error_info(shdata, input, begin + i, 1);
		return (1);
	}

	return (0);
}
