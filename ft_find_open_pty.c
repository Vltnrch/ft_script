/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_open_pty.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/03 15:47:04 by vroche            #+#    #+#             */
/*   Updated: 2015/10/06 12:17:14 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

static void	ft_init_str_ptytty(char *ptyname, char *ttyname)
{
	ft_memset(ptyname, 0, PTY_LEN + 1);
	ft_memset(ttyname, 0, PTY_LEN + 1);
	ft_strncpy(ptyname, PTY_BASE, PTY_BASE_LEN);
}

static void	ft_strcpy_tty(char *ttyname, char x, char y)
{
	ft_strncpy(ttyname, TTY_BASE, PTY_BASE_LEN);
	*(ttyname + PTY_BASE_LEN) = x;
	*(ttyname + PTY_BASE_LEN + 1) = y;
}

int			ft_find_open_pty(char *ttyname)
{
	int		ptyfd;
	char	*x;
	char	*y;
	char	ptyname[PTY_LEN + 1];

	ft_init_str_ptytty(ptyname, ttyname);
	x = X;
	while (*x != '\0')
	{
		*(ptyname + PTY_BASE_LEN) = *x;
		y = Y;
		while (*y != '\0')
		{
			*(ptyname + PTY_BASE_LEN + 1) = *y;
			ptyfd = open(ptyname, O_RDWR);
			if (ptyfd != -1)
			{
				ft_strcpy_tty(ttyname, *x, *y);
				return (ptyfd);
			}
			y++;
		}
		x++;
	}
	return (-1);
}
