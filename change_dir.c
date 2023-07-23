#include "shs.h"

/**
 * cd_dir - Changes the current directory.
 * @shdata: Data relevant.
 * Return: 1 on success.
 */
int cd_dir(shell_data *shdata)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = shdata->args[1];

	if (dir)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	/* Check for special directory names */
	if (!dir || !ishome || !ishome2 || !isddash)
	{
		cd_home(shdata);
		return (1);
	}

	/* Handle the "-" option */
	if (_strcmp("-", dir) == 0)
	{
		cd_go_back(shdata);
		return (1);
	}

	/* Handle "." and ".." directories */
	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_per(shdata);
		return (1);
	}

	/* Handle other directory paths */
	cd_goto(shdata);

	return (1);
}

/**
 * cd_per - changes to the parent directory
 *
 * @shdata: data relevant (environ)
 *
 * Return: no return
 */
void cd_per(shell_data *shdata)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *parent_dir;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = _strdup(pwd);
	set_env_var("OLDPWD", cp_pwd, shdata);
	dir = shdata->args[1];

	if (_strcmp(".", dir) == 0)
	{
		set_env_var("PWD", cp_pwd, shdata);
		free(cp_pwd);
		return;
	}

	parent_dir =  dirname(cp_pwd);
	if (chdir(parent_dir) == -1)
	{
		error_code(shdata, 2);
		free(cp_pwd);
		return;
	}

	set_env_var("PWD", parent_dir, shdata);
	shdata->status = 0;
	free(cp_pwd);
}

/**
 * cd_goto - changes to a directory given
 * by the user
 *
 * @shdata: data relevant (directories)
 * Return: no return
 */
void cd_goto(shell_data *shdata)
{
	char pwd[PATH_MAX];
	char *dir, *cp_pwd, *cp_dir;

	getcwd(pwd, sizeof(pwd));

	dir = shdata->args[1];
	if (chdir(dir) == -1)
	{
		error_code(shdata, 2);
		return;
	}

	cp_pwd = _strdup(pwd);
	set_env_var("OLDPWD", cp_pwd, shdata);

	cp_dir = _strdup(dir);
	set_env_var("PWD", cp_dir, shdata);

	free(cp_pwd);
	free(cp_dir);

	shdata->status = 0;

	chdir(dir);
}

/**
 * cd_go_back - changes to the previous directory
 *
 * @shdata: data relevant (environ)
 * Return: no return
 */
void cd_go_back(shell_data *shdata)
{
	char *p_oldpwd, *cp_pwd, *cp_oldpwd;

	cp_pwd = _strdup(getcwd(NULL, 0));
	p_oldpwd = _getenv("OLDPWD", shdata->_environ);

	if (!p_oldpwd)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = _strdup(p_oldpwd);

	set_env_var("OLDPWD", cp_pwd, shdata);

	if (chdir(cp_oldpwd) == -1)
		set_env_var("PWD", cp_pwd, shdata);
	else
		set_env_var("PWD", cp_oldpwd, shdata);

	write(STDOUT_FILENO, cp_pwd, _strlen(cp_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	shdata->status = 0;

	chdir(cp_pwd);
}

/**
 * cd_home - changes to home directory
 *
 * @shdata: data relevant (environ)
 * Return: no return
 */
void cd_home(shell_data *shdata)
{
	char *p_pwd, *home;
	char *cp_pwd = _strdup(getcwd(NULL, 0));
	(void) p_pwd;

	home = _getenv("HOME", shdata->_environ);

	if (!home)
	{
		set_env_var("OLDPWD", cp_pwd, shdata);
		free(cp_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		error_code(shdata, 2);
		free(cp_pwd);
		return;
	}

	set_env_var("OLDPWD", cp_pwd, shdata);
	set_env_var("PWD", home, shdata);
	free(cp_pwd);
	shdata->status = 0;
}
