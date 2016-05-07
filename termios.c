/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 18:32:18 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/06 18:15:59 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		reset_term(void)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag = (ICANON | ECHO);
	if (tcsetattr(0, 0, &term) == -1)
		return (-1);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_int);
	return (0);
}

int		init_term(void)
{
	struct termios	term;
	char			*name_term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) != 1)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_int);
	return (0);
}
	
void	win_size(t_intel *node, t_struct *info)
{
	struct winsize	win;
	
	ioctl(0, TIOCGWINSZ, &win);
	info->col = win.ws_col;
	info->row = win.ws_row;
	longest_word(node, info);
	print_lst(node, info);
	tputs(tgoto(tgetstr("UP", NULL), 0, info->size_last), 0, ft_putchar_int);
	tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
}
