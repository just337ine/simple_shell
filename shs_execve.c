#include "shs.h"

/**
 * is_current_dir - checks if ":" is in the current directory path
 * @path: pointer to the path string
 * @i: pointer to the index
 * Return: 1 if the path contains ":", 0 otherwise
 */
int is_current_dir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
		(*i)++;

	if (path[*i])
		(*i)++;

	return (0);
}

/**
 * _which - locates a command
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command
 */
char *_which(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_current_dir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * is_execve - determines if a command is executable
 * @shdata: data structure
 * Return: 0 if the command is not executable, otherwise the index of '/'
 */
int is_execve(shell_data *shdata)
{
	struct stat st;
	int i;
	char *input;

	input = shdata->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	error_code(shdata, 127);
	return (-1);
}

/**
 * check_cmd_error - verifies if the user has permission to access a command
 * @dir: destination directory
 * @shdata: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_cmd_error(char *dir, shell_data *shdata)
{
	if (!dir)
	{
		error_code(shdata, 127);
		return (1);
	}

	if (_strcmp(shdata->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			error_code(shdata, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(shdata->args[0], X_OK) == -1)
		{
			error_code(shdata, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * cmd_execve - executes command lines
 * @shdata: data structure containing the arguments and input
 * Return: 1 on success
 */
int cmd_execve(shell_data *shdata)
{
	pid_t pd;
	pid_t wpd;
	int state;
	int exec;
	char *dir;
	(void) wpd;

	exec = is_execve(shdata);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _which(shdata->args[0], shdata->_environ);
		if (check_cmd_error(dir, shdata) == 1)
			return (1);
	}

	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _which(shdata->args[0], shdata->_environ);
		else
			dir = shdata->args[0];
		execve(dir + exec, shdata->args, shdata->_environ);
	}
	else if (pd < 0)
	{
		perror(shdata->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	shdata->status = state / 256;
	return (1);
}
