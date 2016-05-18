/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/13 18:32:18 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/18 16:58:46 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			reset_term(t_struct *info)
{
	if (tcgetattr(0, &(info->term)) == -1)
		return (-1);
	info->term.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(0, 0, &(info->term)) == -1)
		return (-1);
	tputs(tgetstr("ve", NULL), 1, ft_putchar_int);
	return (0);
}

int			init_term(t_struct *info)
{
	char			*name_term;

	if ((name_term = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name_term) != 1)
		return (-1);
	if (tcgetattr(0, &(info->term)) == -1)
		return (-1);
	info->term.c_lflag &= ~(ICANON | ECHO);
	info->term.c_cc[VMIN] = 1;
	info->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &(info->term)) == -1)
		return (-1);
	tputs(tgetstr("vi", NULL), 1, ft_putchar_int);
	return (0);
}

t_struct	*stock_struct(t_struct *info, int i)
{
	static t_struct *tmp = NULL;

	if (i == 0)
		tmp = info;
	return (tmp);
}

t_struct	*init_struct(char **argv)
{
	t_struct	*info;

	if (!(info = (t_struct *)malloc(sizeof(t_struct))))
		return (NULL);
	info->node = init_lst(argv);
	info->node->head->line = 1;
	return (info);
}

void		win_size(int id)
{
	t_struct		*info;
	struct winsize	win;

	(void)id;
	info = NULL;
	info = stock_struct(info, 1);
	ioctl(0, TIOCGWINSZ, &win);
	info->col = win.ws_col;
	info->row = win.ws_row;
	longest_word(info);
	info->nb_item = (info->node->length) / info->nb_col;
	if (((info->node->length) % info->nb_col) != 0)
		info->nb_item += 1;
	check_size(info);
}
