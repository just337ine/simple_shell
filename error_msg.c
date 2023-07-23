#include "shs.h"

/**
 * strcat_error_msg - Concatenates the error message for the cd command.
 *
 * @shdata: Data structure containing relevant information.
 * @msg: Message to print.
 * @error: Output error message.
 * @var_str: Counter lines.
 *
 * Return: Error message.
 */
char *strcat_error_msg(shell_data *shdata,
		char *msg, char *error, char *var_str)
{
	char *illegal_flag;

	/* Copy program name*/
	_strcpy(error, shdata->av[0]);

	/* Concatenate ": ", counter, ": ", and command */
	_strcat(error, ": ");
	_strcat(error, var_str);
	_strcat(error, ": ");
	_strcat(error, shdata->args[0]);

	/* Concatenate error message */
	_strcat(error, msg);

	/* Check if an illegal flag is present */
	if (shdata->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = shdata->args[1][1];
		illegal_flag[2] = '\0';

		/* Concatenate illegal flag */
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		/* Concatenate argument */
		_strcat(error, shdata->args[1]);
	}

	/* Concatenate new line and null terminator */
	_strcat(error, "\n");
	_strcat(error, "\0");

	return (error);
}

/**
 * error_env - Generates an error message for the env command in get_env.
 *
 * @shdata: Data structure containing relevant information.
 *
 * Return: Error message.
 */
char *error_env(shell_data *shdata)
{
	int length;
	char *error;
	char *var_str;
	char *msg;

	var_str = int_to_string(shdata->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(shdata->av[0]) + _strlen(var_str);
	length += _strlen(shdata->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(error);
		free(var_str);
		return (NULL);
	}

	/* Concatenate program name, counter, command, and error message */
	_strcpy(error, shdata->av[0]);
	_strcat(error, ": ");
	_strcat(error, var_str);
	_strcat(error, ": ");
	_strcat(error, shdata->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(var_str);

	return (error);
}

/**
 * error_path_126 - Generates an error
 * message for path and permission denied (126).
 *
 * @shdata: Data structure containing relevant information.
 *
 * Return: Error message.
 */
char *error_path_126(shell_data *shdata)
{
	int length;
	char *var_str;
	char *error;

	var_str = int_to_string(shdata->counter);
	length = _strlen(shdata->av[0]) + _strlen(var_str);
	length += _strlen(shdata->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(error);
		free(var_str);
		return (NULL);
	}

	/* Concatenate program name, counter, command, and error message */
	_strcpy(error, shdata->av[0]);
	_strcat(error, ": ");
	_strcat(error, var_str);
	_strcat(error, ": ");
	_strcat(error, shdata->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(var_str);

	return (error);
}


/**
 * error_message - Generates the error message for the cd command.
 *
 * @shdata: Data structure containing relevant information.
 *
 * Return: Error message.
 */
char *error_message(shell_data *shdata)
{
	int length, len_id;

	char *error, *var_str, *msg;

	var_str = int_to_string(shdata->counter);

	/* Check if an illegal option or directory is present */
	if (shdata->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(shdata->args[1]);
	}

	length = _strlen(shdata->av[0]) + _strlen(shdata->args[0]);
	length += _strlen(var_str) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(var_str);
		return (NULL);
	}

	error = strcat_error_msg(shdata, msg, error, var_str);

	free(var_str);

	return (error);
}

/**
 * cmd_not_found - Generates a generic error message for a command not found.
 *
 * @shdata: Data structure containing relevant information.
 *
 * Return: Error message.
 */
char *cmd_not_found(shell_data *shdata)
{
	int length;
	char *error;
	char *var_str;

	var_str = int_to_string(shdata->counter);
	length = _strlen(shdata->av[0]) + _strlen(var_str);
	length += _strlen(shdata->args[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(error);
		free(var_str);
		return (NULL);
	}

	/* Concatenate program name, counter, command, and error message */
	_strcpy(error, shdata->av[0]);
	_strcat(error, ": ");
	_strcat(error, var_str);
	_strcat(error, ": ");
	_strcat(error, shdata->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(var_str);

	return (error);
}
