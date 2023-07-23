#include "shs.h"

/**
 * main - Entry point
 *
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success.
 */
int main(int ac, char **av)
{
	shell_data shdata;
	(void) ac;

	signal(SIGINT, get_signal);
	set_data(&shdata, av);
	shell_prompt(&shdata);
	free_data(&shdata);
	if (shdata.status < 0)
		return (255);
	return (shdata.status);
}

/**
 * free_data - frees data structure
 *
 * @shdata: data structure
 * Return: no return
 */
void free_data(shell_data *shdata)
{
	unsigned int i;

	for (i = 0; shdata->_environ[i]; i++)
	{
		free(shdata->_environ[i]);
	}

	free(shdata->_environ);
	free(shdata->pid);
}

/**
 * set_data - Initialize data structure
 *
 * @shdata: data structure
 * @av: argument vector
 * Return: no return
 */
void set_data(shell_data *shdata, char **av)
{
	unsigned int i;

	shdata->av = av;
	shdata->input = NULL;
	shdata->args = NULL;
	shdata->status = 0;
	shdata->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	shdata->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		shdata->_environ[i] = _strdup(environ[i]);
	}

	shdata->_environ[i] = NULL;
	shdata->pid = int_to_string(getpid());
}

/**
 * shell_prompt - Loop of shell
 * @shdata: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shell_prompt(shell_data *shdata)
{
	int should_continue, i_eof;
	char *input;

	should_continue = 1;
	while (should_continue == 1)
	{
		write(STDIN_FILENO, "^J-S^ > ", 8);
		input = _get_line(&i_eof);
		if (i_eof != -1)
		{
			input = without_comment(input);
			if (input == NULL)
				continue;

			if (check_syntax_error(shdata, input) == 1)
			{
				shdata->status = 2;
				free(input);
				continue;
			}

			input = rep_str_var(input, shdata);
			should_continue = div_commands(shdata, input);
			shdata->counter += 1;
			free(input);
		}
		else
		{
			should_continue = 0;
			free(input);
		}
	}
}



/**
 * get_signal - Handle the Ctrl+C call in the prompt
 * @s: Signal handler
 */
void get_signal(int s)
{
	(void)s;
	write(STDOUT_FILENO, "\n^J-S^ > ", 8);
}
