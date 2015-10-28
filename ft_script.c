/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/06 12:48:28 by vroche            #+#    #+#             */
/*   Updated: 2015/10/10 13:33:39 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

void		ft_script_child(int ptyfd, char *ttyname, char **argv, char **env)
{
	int				ttyfd;
	struct winsize	ws;

	if (setsid() == -1)
		ft_perror_exit("setsid failed");
	if (close(ptyfd) == -1)
		ft_perror_exit("child failed to close tty");
	if (ioctl(0, TIOCGWINSZ, &ws) < 0)
		ft_perror_exit("failed to get window size ioctl");
	if ((ttyfd = open(ttyname, O_RDWR)) == -1)
		ft_perror_exit("child failed to open tty");
	if (ioctl(ttyfd, TIOCSWINSZ, &ws) < 0)
		ft_perror_exit("failed to put window size ioctl");
	if (dup2(ttyfd, 0) != 0)
		ft_perror_exit("dup2 ttyfd to 0 failed");
	if (dup2(ttyfd, 1) != 1)
		ft_perror_exit("dup2 ttyfd to 1 failed");
	if (dup2(ttyfd, 2) != 2)
		ft_perror_exit("dup2 ttyfd to 2 failed");
	if (close(ttyfd) == -1)
		ft_perror_exit("child failed to close tty");
	ft_execve(env, argv);
}

static void	ft_script_daddy_stdintopty(int ptyfd, char *file, \
									int *opt, t_scrpt *scrpt)
{
	char			buf[BUF_SIZE];
	ssize_t			numread;

	numread = read(0, buf, BUF_SIZE);
	if (numread <= 0)
		ft_script_exit(&(scrpt->save), file, scrpt->filefd, opt);
	if (write(ptyfd, buf, numread) != numread)
		ft_perror_restore_exit("write failed on pty", &(scrpt->save));
}

static void	ft_script_daddy_ptytofile(int ptyfd, char *file, \
									int *opt, t_scrpt *scrpt)
{
	char			buf[BUF_SIZE];
	ssize_t			numread;

	numread = read(ptyfd, buf, BUF_SIZE);
	if (numread <= 0)
		ft_script_exit(&(scrpt->save), file, scrpt->filefd, opt);
	if (write(1, buf, numread) != numread)
		ft_perror_restore_exit("write failed on stdin", &(scrpt->save));
	if (write(scrpt->filefd, buf, numread) != numread)
		ft_perror_restore_exit("write failed on typescript file", \
								&(scrpt->save));
}

static void	ft_print_time(t_scrpt *scrpt, char *file)
{
	time_t			t;

	t = time(NULL);
	ft_printf("Script started, output file is %s\n", file);
	ft_dprintf(scrpt->filefd, "Script started on %s", ctime(&t));
}

void		ft_script_daddy(int ptyfd, int *opt, char *file)
{
	fd_set			fds;
	t_scrpt			scrpt;

	scrpt.filefd = open(file, (opt[0] == 1 ? O_O_A : O_O), O_S);
	if (scrpt.filefd == -1)
		ft_perror_exit("failed to open script file");
	if (!opt[1])
		ft_print_time(&scrpt, file);
	if (ioctl(0, TIOCGETA, &(scrpt.save)) == -1)
		ft_perror_exit("save termios struct failed");
	ft_init_term();
	while (42 == 42)
	{
		FD_ZERO(&fds);
		FD_SET(0, &fds);
		FD_SET(ptyfd, &fds);
		if (select(ptyfd + 1, &fds, NULL, NULL, NULL) == -1)
			ft_perror_restore_exit("select", &(scrpt.save));
		if (FD_ISSET(0, &fds))
			ft_script_daddy_stdintopty(ptyfd, file, opt, &scrpt);
		if (FD_ISSET(ptyfd, &fds))
			ft_script_daddy_ptytofile(ptyfd, file, opt, &scrpt);
	}
}
