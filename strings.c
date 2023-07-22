#include "shs.h"

/**
 * _strdup - Duplicate a string in heap memory.
 *
 * @s: String to duplicate.
 *
 * Return: Pointer to the duplicated string,
 * or NULL if memory allocation fails.
 */
char *_strdup(const char *s)
{
	char *new;
	size_t len;

	len = _strlen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	_memcpy(new, s, len + 1);
	return (new);
}

/**
 * _strlen - Get the length of a string.
 *
 * @s: String to calculate the length of.
 *
 * Return: Length of the string.
 */
size_t _strlen(const char *s)
{
	size_t len;

	for (len = 0; s[len] != '\0'; len++)
	{
	}
	return (len);
}

/**
 * comp_chars - Compare characters of strings.
 *
 * @str: Input string.
 * @delim: Delimiter.
 *
 * Return: 1 if the characters are equal, 0 if they are not.
 */
int comp_chars(const char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _strtok - Split a string by a delimiter.
 *
 * @str: Input string.
 * @delim: Delimiter.
 *
 * Return: The next token in the string, or NULL if no more tokens are found.
 */
char *_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (comp_chars(str, delim))
			return (NULL);
		splitted = str; /* Store first address */
		i = _strlen(str);
		str_end = &str[i]; /* Store last address */
	}
	str_start = splitted;
	if (str_start == str_end) /* Reach the end */
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/* Breaking loop finding the next token */
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/* Replacing delimiter with null character */
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /* Str != Delim */
			bool = 1;
	}
	if (bool == 0) /* Str == Delim */
		return (NULL);
	return (str_start);
}

/**
 * _isdigit - Check if a string consists of digits.
 *
 * @s: Input string.
 *
 * Return: 1 if the string consists of digits, 0 otherwise.
 */
int _isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}
	return (1);
}

/**
 * _strcat - Concatenate two strings.
 *
 * @dest: Destination string.
 * @src: Source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcat(char *dest, const char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * _strcpy - Copy the string pointed to by src.
 *
 * @dest: Destination string.
 * @src: Source string.
 *
 * Return: Pointer to the destination string.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		dest[a] = src[a];
	}
	dest[a] = '\0';

	return (dest);
}

/**
 * _strcmp - Compare two strings.
 *
 * @s1: First string.
 * @s2: Second string.
 *
 * Return: Negative value if s1 is less than s2,
 * positive value if s1 is greater than s2, 0 if s1 is equal to s2.
 */
int _strcmp(const char *s1, const char *s2)
{
	int i;

	for (i = 0; s1[i] == s2[i] && s1[i] != '\0'; i++)
		;

	if (s1[i] > s2[i])
		return (1);
	if (s1[i] < s2[i])
		return (-1);
	return (0);
}

/**
 * _strchr - Locate a character in a string.
 *
 * @s: String to search in.
 * @c: Character to locate.
 *
 * Return: Pointer to the first occurrence of the character c in the string s,
 * or NULL if the character is not found.
 */
char *_strchr(const char *s, int c)
{
	unsigned int i = 0;

	for (; s[i] != '\0'; i++)
		if (s[i] == c)
			return ((char *)(s + i));
	if (s[i] == c)
		return ((char *)(s + i));
	return (NULL);
}

/**
 * _strspn - Get the length of a prefix substring.
 *
 * @s: Initial segment.
 * @accept: Accepted bytes.
 *
 * Return: Number of accepted bytes.
 */
size_t _strspn(const char *s, const char *accept)
{
	size_t i, j;
	int bool;

	for (i = 0; s[i] != '\0'; i++)
	{
		bool = 1;
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}
