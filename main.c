/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 18:49:21 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/18 18:41:26 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

char	*do_select(char **argv, int id)
{
	t_struct	*info;
	char		*str;

	info = init_struct(argv);
	info->fd = open(ttyname(0), O_RDWR);
	if (info->fd == -1)
		return (NULL);
	if (init_term(info) == -1)
		return (NULL);
	tputs(tgetstr("cl", NULL), 1, ft_putchar_int);
	tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
	stock_struct(info, 0);
	win_size(id);
	while (1)
	{
		str = deal_with_term(info);
		if (str)
			break ;
	}
	if (reset_term(info) == -1)
		return (NULL);
	if (close(info->fd) < 0)
		ft_putendl_fd("Can't close fd", 2);
	return (str);
}

int		main(int argc, char **argv)
{
	char		*str;
	int			id;

	id = 0;
	signal(SIGINT, SIG_IGN);
	ft_signal(id);
	if (argc >= 2)
		str = do_select(argv, id);
	else
	{
		ft_putendl_fd("Too few argument to function call", 2);
		return (1);
	}
	if (str)
	{
		ft_putendl(str);
		free(str);
	}
	return (0);
}
