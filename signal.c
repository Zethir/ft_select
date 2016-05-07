/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 15:55:11 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/07 18:16:57 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	catch_signal(int i)
{
	struct termios	term;
	char	cp[2];

	if (i == SIGCONT)
	{	
		init_term();
		signal(SIGTSTP, catch_signal);
	}
	else if (i == SIGTSTP)
	{	
		cp[0] = term.c_cc[VSUSP];
		cp[1] = 0;
		reset_term();
		signal(SIGTSTP, SIG_DFL);
		clean_lst();
		ioctl(0, TIOCSTI, cp);
	}
	else if (i == SIGWINCH)
		ft_putchar(0);
}

void		ft_signal(t_intel *node, t_struct *info)
{
	char	buff[1];
	int		i;

	i = 1;
	while (i < 32)
	{
		signal(i, catch_signal);
		i++;
	}
	read(1, buff, 1);
	if (*buff == 0)
		win_size(node, info);
}
