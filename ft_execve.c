/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/10 12:17:41 by vroche            #+#    #+#             */
/*   Updated: 2015/10/28 19:14:34 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

static int	ft_strjoin_path(char **path, char *arg, char *buff)
{
	char *tmp;

	tmp = *path;
	ft_bzero(buff, 1024);
	if (!*tmp)
		return (0);
	while (*tmp && *tmp != ':')
		*buff++ = *tmp++;
	*buff++ = '/';
	*path = tmp;
	while (*arg)
		*buff++ = *arg++;
	return (1);
}

static void	ft_execve_error(char *s1, char *s2)
{
	ft_dprintf(2, "ft_script: %s%s\n", s1, s2);
	_exit(EXIT_FAILURE);
}

static void	ft_execve_arg(char **argv, char **env)
{
	char	*tmp;
	char	buff[1024];

	if (**argv == '.' || **argv == '/')
	{
		ft_strcpy(buff, *argv);
		if (access(buff, F_OK))
			ft_execve_error(*argv, ": No such file or directory");
	}
	else
	{
		if (!(tmp = ft_get_var_env(env, "PATH")))
			tmp = DEF_PATH;
		while (ft_strjoin_path(&tmp, *argv, buff))
		{
			if (access(buff, F_OK) == 0)
				break ;
			tmp++;
		}
		if (!*tmp)
			ft_execve_error(*argv, ": No such file or directory");
	}
	if (access(buff, X_OK))
		ft_execve_error(*argv, ": Permission denied.\n");
	execve(buff, argv, env);
}

void		ft_execve(char **env, char **argv)
{
	char	*tmp;
	char	*tmp2[2];

	if (argv)
		argv++;
	if (argv && *argv)
		ft_execve_arg(argv, env);
	else if ((tmp = ft_get_var_env(env, "SHELL")) != NULL)
	{
		tmp2[0] = tmp;
		tmp2[1] = NULL;
		execve(tmp, tmp2, env);
	}
	else
		execve("/bin/sh", NULL, NULL);
	ft_perror_exit("WTF are you doing here !");
}
