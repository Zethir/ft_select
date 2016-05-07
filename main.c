/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/22 18:49:21 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/07 18:08:27 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

char	*do_select(t_intel *node, t_struct *info)
{
	char		*str;

	if (init_term() == -1)
		return (NULL);
	tputs(tgetstr("cr", NULL), 1, ft_putchar_int);
	tputs(tgetstr("sc", NULL), 1, ft_putchar_int);
	win_size(node, info);
	while (1)
	{
		str = deal_with_term(node, info);
		if (str)
			break;
	}
	if (reset_term() == -1)
		return (NULL);
	return (str);
}

int		main(int argc, char **argv)
{
	t_intel		*node;
	t_struct	*info;
	char		*str;
	
	if (!(info = (t_struct *)malloc(sizeof(t_struct))))
		return (-1);
	info->i[1] = 1;
	info->i[0] = 0;
	if (argc >= 2)
	{	
		node = init_lst(argv);
		signal(SIGINT, SIG_IGN);
		ft_signal(node, info);
		str = do_select(node, info);
	}
	else
	{
		ft_putendl_fd("Too few argument to function call", 2);
		return (1);
	}
	if (str)
		ft_putendl(str);
	return (0);
}
