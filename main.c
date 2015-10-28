/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/02 17:46:00 by vroche            #+#    #+#             */
/*   Updated: 2015/10/09 18:35:25 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"
#include <stdio.h>

static void	ft_prepare(char **argv, int ptyfd, char *ttyname, char **env)
{
	int		opt[2];
	char	**tmp;
	int		forkpid;

	opt[0] = 0;
	opt[1] = 0;
	tmp = ft_check_arg(argv, &opt[0], &opt[1]);
	if ((forkpid = fork()) == -1)
		ft_perror_exit("fork failed");
	if (forkpid == 0)
		ft_script_child(ptyfd, ttyname, tmp, env);
	else
		ft_script_daddy(ptyfd, opt, (tmp == NULL ? "typescript" : *tmp));
}

int			main(int argc, char **argv, char **env)
{
	char	ttyname[PTY_LEN + 1];
	int		ptyfd;
	char	**tmp;

	tmp = argv;
	if (argc == 0)
		return (-1);
	if ((ptyfd = ft_find_open_pty(ttyname)) == -1)
		ft_perror_exit("Impossible to find or open pty");
	ft_prepare(argv, ptyfd, ttyname, env);
	return (0);
}
