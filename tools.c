/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 16:23:23 by cboussau          #+#    #+#             */
/*   Updated: 2016/05/18 18:11:01 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	free_lst(t_struct *info)
{
	t_lst	*ptr;

	ptr = info->node->head;
	while (ptr)
	{
		if (ptr->name)
			ft_strdel(&ptr->name);
		if (ptr->save)
			ft_strdel(&ptr->save);
		ptr = ptr->next;
	}
}

void	left_arrow(t_struct *info, t_lst *ptr)
{
	size_t	i;

	i = info->nb_item;
	while (i-- != 0)
	{
		if (ptr == info->node->head)
		{
			ptr = info->node->tail;
			if (i >= info->nb_item - info->size_last)
				i -= info->nb_item - info->size_last;
			else
			{
				i = 0;
				break ;
			}
		}
		ptr = ptr->prev;
	}
	ptr->line = 1;
}

void	right_arrow(t_struct *info, t_lst *ptr)
{
	size_t	i;

	i = info->nb_item;
	while (i-- != 0)
	{
		if (ptr == info->node->tail)
		{
			ptr = info->node->head;
			if (i >= info->nb_item - info->size_last)
				i -= info->nb_item - info->size_last;
			else
			{
				i = 0;
				break ;
			}
		}
		ptr = ptr->next;
	}
	ptr->line = 1;
}

void	check_size(t_struct *info)
{
	if (info->nb_item >= info->row || info->size_w + 2 >= info->col)
	{
		clean_lst(info);
		ft_putstr_fd("Window is too small", 2);
	}
	else
		print_lst(info);
}

void	start_end(t_struct *info)
{
	t_lst	*ptr;

	ptr = info->node->head;
	if (info->buff[0] == 27 && info->buff[1] == 91 && info->buff[2] == 72)
	{
		while (ptr->line != 1)
			ptr = ptr->next;
		ptr->line = 0;
		ptr = info->node->head;
		ptr->line = 1;
	}
	if (info->buff[0] == 27 && info->buff[1] == 91 && info->buff[2] == 70)
	{
		while (ptr->line != 1)
			ptr = ptr->next;
		ptr->line = 0;
		ptr = info->node->tail;
		ptr->line = 1;
	}
}
