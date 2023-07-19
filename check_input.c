#include "shs.h"

/**
 * check_env_var - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void check_env_var(store_var **h, char *in, shell_data *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_store_var_node(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_store_var_node(h, j, NULL, 0);
}

/**
 * check_var_typed - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int check_var_typed(store_var **h, char *in, char *st, shell_data *data)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_store_var_node(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_store_var_node(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_store_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_store_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_store_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_store_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_store_var_node(h, 0, NULL, 0);
			else
				check_env_var(h, in + i, data);
		}
	}

	return (i);
}

/**
 * replace_str_var - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replace_str_var(store_var **head, char *input, char *new_input, int nlen)
{
	store_var *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * rep_str_var - calls functions to replace string into vars
 *
 * @input: input string
 * @shdata: data structure
 * Return: replaced string
 */
char *rep_str_var(char *input, shell_data *shdata)
{
	store_var *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = int_to_string(shdata->status);
	head = NULL;

	olen = check_var_typed(&head, input, status, shdata);

	if (!head)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replace_str_var(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_store_var_list(&head);

	return (new_input);
}
