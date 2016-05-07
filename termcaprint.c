/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 22:02:17 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/06 18:56:46 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	delete_elem(t_intel *node, t_lst *ptr)
{
	t_lst	*del;

	del = ptr;
	if (del == node->head)
		node->head = del->next;
	if (del->next != NULL)
		del->next->prev = del->prev;
	if (del->prev != NULL)
		del->prev->next = del->next;
	free (del);
	node->length -= 1;
	if (node->length == 0)
	{
		tputs(tgetstr("ue", NULL), 0, ft_putchar_int);
		ft_putendl_fd("There is no elements in this list anymore.", 2);
		exit (-1);
	}
}

static void	print_standout(t_lst *ptr)
{
	tputs(tgetstr("mr", NULL), 0, ft_putchar_int);
	ft_putstr_fd("\033[31m", 2);
	ft_putendl(ptr->name);
	ptr->select = 1;
	ft_putstr_fd("\e[00m", 2);
	ptr->save = ft_strdup(ptr->name);
	tputs(tgetstr("me", NULL), 0, ft_putchar_int);
}

static void	print_underline(t_intel *node, t_lst *ptr, t_struct *info)
{
	tputs(tgetstr("us", NULL), 0, ft_putchar_int);
	if (info->buff[0] == ' ' && ptr->select == 0)
		print_standout(ptr);
	else if (info->buff[0] == ' ' && ptr->select == 1)
	{
		ft_putstr_fd("\033[1;34m", 2);
		ft_putendl(ptr->name);
		ft_putstr_fd("\e[00m", 2);
		bzero(ptr->save, ft_strlen(ptr->save));
		ptr->select = 0;
	}
	else if (info->buff[0] == 127 || (info->buff[0] == 27
				&& info->buff[1] == 91 && info->buff[2] == 51))
		delete_elem(node, ptr);
	else if (ptr->select == 1)
		print_standout(ptr);
	else
	{
		ft_putstr_fd("\033[1;34m", 2);
		ft_putendl(ptr->name);
		ft_putstr_fd("\e[00m", 2);
	}
	tputs(tgetstr("ue", NULL), 0, ft_putchar_int);
}

void	print_opt(t_intel *node, t_lst *ptr, t_struct *info)
{
	if (info->i[1] == info->index[1] && info->i[0] == info->index[0])
		print_underline(node, ptr, info);
	else if (ptr->select == 1)
		print_standout(ptr);
	else
	{
		ft_putstr_fd("\e[97m", 2);
		ft_putendl(ptr->name);
		ft_putstr_fd("\e[00m", 2);
	}
}
