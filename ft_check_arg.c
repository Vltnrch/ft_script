/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/06 14:55:28 by vroche            #+#    #+#             */
/*   Updated: 2015/10/07 16:01:51 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

static void	ft_usage(char *arg, char c)
{
	ft_dprintf(2, "%s: illegal option -- %c\n", arg, c);
	ft_putstr_fd("usage: ft_script [-aq] [file [command ...]]\n", 2);
}

static void	ft_check_opt(char *tmp, char *argv, int *a, int *q)
{
	argv++;
	while (*argv)
	{
		if (*argv == 'a')
			*a = 1;
		else if (*argv == 'q')
			*q = 1;
		else
			ft_usage(tmp, *argv);
		argv++;
	}
}

char		**ft_check_arg(char **argv, int *a, int *q)
{
	char	*tmp;

	tmp = *argv;
	argv++;
	while (argv && *argv && **argv == '-')
	{
		ft_check_opt(tmp, *argv, a, q);
		argv++;
	}
	if (*argv > 0)
		return (argv);
	return (NULL);
}
