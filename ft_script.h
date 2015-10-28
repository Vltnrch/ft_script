/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vroche <vroche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/02 16:50:47 by vroche            #+#    #+#             */
/*   Updated: 2015/10/28 19:02:55 by vroche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H

# include <termios.h>
# include <sys/ioctl.h>
# include <fcntl.h>
# include <unistd.h>
# include <time.h>
# include "libft.h"
# include "ft_printf.h"

# define PTY_BASE "/dev/pty"
# define TTY_BASE "/dev/tty"
# define PTY_BASE_LEN (8)
# define PTY_LEN (PTY_BASE_LEN + 2)
# define X "pqrstuvwxyzabcde"
# define Y "0123456789abcdef"
# define BUF_SIZE 1024
# define DEF_PATH "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# define O_O (O_WRONLY | O_CREAT | O_TRUNC)
# define O_O_A (O_WRONLY | O_CREAT | O_APPEND)
# define O_S S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

typedef struct		s_scrpt
{
	int				filefd;
	struct termios	save;
}					t_scrpt;

void				ft_perror_exit(const char *str);
void				ft_init_term(void);
void				ft_script_exit(struct termios *t, char *file, \
									int filefd, int *opt);
char				*ft_get_var_env(char **env, char *var);
void				ft_perror_restore_exit(const char *str, struct termios *t);

int					ft_find_open_pty(char *ttyname);

void				ft_script_child(int ptyfd, char *ttyname, \
									char **argv, char **env);
void				ft_script_daddy(int ptyfd, int *opt, char *file);

char				**ft_check_arg(char **argv, int *a, int *q);

void				ft_execve(char **env, char **av);

#endif
