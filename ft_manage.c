/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_manage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/02 17:41:36 by vroche            #+#    #+#             */
/*   Updated: 2015/10/10 12:20:43 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

void	ft_perror_exit(const char *str)
{
	ft_putstr_fd("Error : ", 2);
	ft_putendl_fd(str, 2);
	_exit(EXIT_FAILURE);
}

void	ft_perror_restore_exit(const char *str, struct termios *t)
{
	if (ioctl(0, TIOCSETA, t) == -1)
		ft_perror_exit("Put original termios struct failed");
	ft_perror_exit(str);
}

void	ft_script_exit(struct termios *t, char *file, int filefd, int *opt)
{
	time_t	ti;

	if (ioctl(0, TIOCSETA, t) == -1)
		ft_perror_exit("Put original termios struct failed");
	if (!opt[1])
	{
		ti = time(NULL);
		ft_dprintf(filefd, "\nScript done on %s", ctime(&ti));
		ft_printf("\nScript done, output file is %s\n", file);
	}
	_exit(EXIT_SUCCESS);
}

void	ft_init_term(void)
{
	struct termios t;

	if (ioctl(0, TIOCGETA, &t) == -1)
		ft_perror_exit("Read termios struct failed");
	t.c_lflag &= ~(ICANON | ISIG | IEXTEN | ECHO);
	t.c_iflag &= ~(BRKINT | ICRNL | IGNBRK | IGNCR | INLCR | \
					INPCK | ISTRIP | IXON | PARMRK);
	t.c_oflag &= ~OPOST;
	t.c_cc[VMIN] = 1;
	t.c_cc[VTIME] = 0;
	if (ioctl(0, TIOCSETAF, &t) == -1)
		ft_perror_exit("Put raw termios struct failed");
}

char	*ft_get_var_env(char **env, char *var)
{
	char	**tmp;
	int		len;

	tmp = env;
	if (!env)
		return (NULL);
	len = ft_strlen(var);
	while (*tmp && ft_strncmp(*tmp, var, len))
		tmp++;
	if (*tmp)
		return (*tmp + len + 1);
	return (NULL);
}
