/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 15:55:11 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/18 17:22:20 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	sigtstp(int id)
{
	char		cp[2];
	t_struct	*info;

	(void)id;
	info = NULL;
	info = stock_struct(info, 1);
	cp[0] = info->term.c_cc[VSUSP];
	cp[1] = 0;
	info->term.c_lflag |= (ICANON | ECHO);
	signal(SIGTSTP, SIG_DFL);
	clean_lst(info);
	tcsetattr(0, 0, &(info->term));
	tputs(tgetstr("ve", NULL), 1, ft_putchar_int);
	ioctl(0, TIOCSTI, cp);
}

void	sigcont(int id)
{
	t_struct	*info;

	(void)id;
	info = NULL;
	info = stock_struct(info, 1);
	init_term(info);
	signal(SIGTSTP, ft_signal);
	win_size(id);
}

void	sigint(int id)
{
	t_struct *info;

	(void)id;
	info = NULL;
	info = stock_struct(info, 1);
	tcsetattr(0, TCSANOW, &(info->term));
	clean_lst(info);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_int);
	free_lst(info);
	exit(0);
}

void	ft_signal(int id)
{
	(void)id;
	signal(SIGWINCH, win_size);
	signal(SIGCONT, sigcont);
	signal(SIGTSTP, sigtstp);
	signal(SIGINT, sigint);
	signal(SIGQUIT, sigint);
	signal(SIGTERM, sigint);
}
