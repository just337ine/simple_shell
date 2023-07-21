#include "shs.h"

/**
 * error_code - calls the error according to the builtin, syntax, or permission
 * @shdata: data structure that contains arguments
 * @eval: error value
 * Return: error value
 */
int error_code(shell_data *shdata, int eval)
{
	char *error = NULL;

	switch (eval)
	{
		case -1:
			error = error_env(shdata);
			break;
		case 126:
			error = error_path_126(shdata);
			break;
		case 127:
			error = cmd_not_found(shdata);
			break;
		case 2:
			if (_strcmp("exit", shdata->args[0]) == 0)
				error = msg_exit_shell(shdata);
			else if (_strcmp("cd", shdata->args[0]) == 0)
				error = error_message(shdata);
			break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));

		free(error);
	}

	shdata->status = eval;
	return (eval);
}

/**
 * get_builtin - returns the function pointer
 * to the corresponding built-in command
 * @cmd: command string
 * Return: function pointer to the built-in command, or NULL if not found
 */
int (*get_builtin(char *cmd))(shell_data *)
{
	built_in builtin[] = {
		{ "env", _env },
		{ "exit", exit_shell },
		{ "setenv", _setenv },
		{ "unsetenv", _delenv },
		{ "cd", cd_dir },
		{ "help", get_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			return (builtin[i].f);
	}

	return (NULL);
}
