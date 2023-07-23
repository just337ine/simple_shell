#include "shs.h"

/**
 * add_store_var_node - Adds a variable at the end of a store_var list.
 *
 * @head: Address of the head of the linked list.
 * @var_length: Length of the variable.
 * @value: Value of the variable.
 * @value_length: Length of the value.
 *
 * Return: Address of the head.
 */
store_var *add_store_var_node(store_var **head,
		int var_length, char *value, int value_length)
{
	store_var *new = malloc(sizeof(*new));

	if (!new)
		return (NULL);

	new->len_var = var_length;
	new->val = value;
	new->len_val = value_length;

	new->next = NULL;

	if (!(*head))
	{
		*head = new;
	}
	else
	{
		store_var *temp = *head;

		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_store_var_list - Frees a store_var list.
 *
 * @head: Address of the head of the linked list.
 *
 * Return: No return.
 */
void free_store_var_list(store_var **head)
{
	if (head)
	{
		store_var *curr = *head;

		while (curr)
		{
			store_var *temp = curr;

			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_div_node_end - Adds a separator found at the end of a div_list.
 *
 * @head: Address of the head of the linked list.
 * @sep: Separator found (; | &).
 *
 * Return: Address of the head.
 */
div_list *add_div_node_end(div_list **head, char sep)
{
	div_list *new = malloc(sizeof(*new));

	if (!new)
		return (NULL);

	new->separator = sep;
	new->next = NULL;

	if (!(*head))
	{
		*head = new;
	}
	else
	{
		div_list *temp = *head;

		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * free_div_list - Frees a div_list.
 *
 * @head: Address of the head of the linked list.
 *
 * Return: No return.
 */
void free_div_list(div_list **head)
{
	if (head)
	{
		div_list *curr = *head;

		while (curr)
		{
			div_list *temp = curr;

			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - Adds a command line at the end of a line_list.
 *
 * @head: Address of the head of the linked list.
 * @line: Command line.
 *
 * Return: Address of the head.
 */
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new = malloc(sizeof(*new));

	if (!new)
		return (NULL);

	new->line = line;
	new->next = NULL;

	if (!(*head))
	{
		*head = new;
	}
	else
	{
		line_list *temp = *head;

		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}
